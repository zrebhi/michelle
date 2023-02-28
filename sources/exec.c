/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:17:49 by zrebhi            #+#    #+#             */
/*   Updated: 2023/02/28 14:30:53 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	ft_builtins(t_minishell *data)
{
	if (!strcmp(data->cmds->full_cmd[0], "pwd"))
		return (ft_built_in_pwd(), 1);
	if (!strcmp(data->cmds->full_cmd[0], "env"))
		return (ft_built_in_env(&data->head_env), 1);
	if (!strcmp(data->cmds->full_cmd[0], "export"))
		return (ft_built_in_export(&data->head_env, data->cmds->full_cmd), 1);
	if (!strcmp(data->cmds->full_cmd[0], "cd"))
		return (1);
	if (!strcmp(data->cmds->full_cmd[0], "unset"))
		return (1);
	return (0);
}

/* Handles the executions of the commands and returns the corresponding error
if the command was not found. */

void	ft_exec(t_minishell *data)
{
	int		i;
	char	*cmd;

	i = -1;
	execve(data->cmds->full_cmd[0], data->cmds->full_cmd, data->envp);
	if (data->paths)
	{
		while (data->paths[++i])
		{
			cmd = ft_strjoin(data->paths[i], data->cmds->full_cmd[0]);
			if (!cmd)
				return ;
			execve(cmd, data->cmds->full_cmd, data->envp);
			free(cmd);
		}
	}
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(data->cmds->full_cmd[0], 2);
	ft_putstr_fd("\n", 2);
	return ;
}

static void	ft_input(t_minishell *data)
{
	size_t	length;
	char	*line;

	if (close(data->end[0]) == -1)
		return (perror("close pipe"));
	while (1)
	{
		line = readline("> ");
		if (!line)
			return ;
		if (ft_strlen(line) - 1 > ft_strlen(data->cmds->limiter))
			length = ft_strlen(line) - 1;
		else
			length = ft_strlen(data->cmds->limiter);
		if (!ft_strncmp(line, data->cmds->limiter, length))
		{
			if (close(data->end[1]) == -1)
				return (perror("close pipe"));
			exit(EXIT_SUCCESS) ;
		}
		ft_putstr_fd(line, data->end[1]);
		ft_putstr_fd("\n", data->end[1]);
		free(line);
	}
}

void	ft_heredoc(t_minishell *data)
{
	pid_t	heredoc_pid;

	if (pipe(data->end) == -1)
		return (perror("heredoc pipe"));
	heredoc_pid = fork();
	if (heredoc_pid == -1)
		return (perror("heredoc fork"));
	if (heredoc_pid != 0 && close(data->end[1]) == -1)
		return ((void)perror("close pipe"));
	if (heredoc_pid == 0)
		ft_input(data);
	waitpid(heredoc_pid, NULL, 0);
	dup2(data->end[0], STDIN_FILENO);
	if (close(data->end[0]) == -1)
		return (perror("close pipe"));
}

/* Handles everything related to children processes. */

void	ft_incubator(t_minishell *data)
{
	if (!data->cmds->here_doc && close(data->end[0]) == -1)
		return (perror("close pipe"));
	if (data->cmds->infile > 0)
		if (dup2(data->cmds->infile, STDIN_FILENO) == -1)
			return ;
	if (data->cmds->outfile > 1)
		if (dup2(data->cmds->outfile, STDOUT_FILENO) == -1)
			return ;
	if (data->cmds->outfile == 0)
		if (dup2(data->end[1], STDOUT_FILENO) == -1)
			return (perror("dup2 end[1]"));
	if (ft_builtins(data))
		exit(0);
	ft_exec(data);
	exit(127);
}

/* Creates a child process for every command and links them together
with pipes */

void	pipex_commands(t_minishell *data)
{
	while (data->cmds)
	{
		if (data->cmds->here_doc == 1)
		{
			if (!data->cmds->limiter)
				return ;
			ft_heredoc(data);
		}
		if (pipe(data->end) == -1)
			return ((void)perror("pipe"));
		data->cmds->cmd_pid = fork();
		if (data->cmds->cmd_pid == -1)
			return ((void)perror("Fork"));
		if (data->cmds->cmd_pid != 0 && close(data->end[1]) == -1)
			return ((void)perror("close pipe"));
		if (data->cmds->cmd_pid == 0)
			ft_incubator(data);
		if (dup2(data->end[0], STDIN_FILENO) == -1)
			return ((void)perror("dup2 end[0]"));
		if (close(data->end[0]) == -1)
			return ((void)perror("close pipe"));
		data->cmds = data->cmds->next;
	}
}

/* Runs our commands with pipex_commands, then closes our remaining fds
and waits for children processes to be done */

void	pipex(t_minishell *data)
{
	int			status;
	t_cmdlist	*head;

	head = data->cmds;
	pipex_commands(data);
	data->cmds = head;
	while (data->cmds)
	{
		if (data->cmds->outfile > 1 && close(data->cmds->outfile) == -1)
			perror("close outfile");
		data->cmds = data->cmds->next;
	}
	data->cmds = head;
	while (data->cmds)
	{
		waitpid(data->cmds->cmd_pid, &status, 0);
		data->cmds = data->cmds->next;
	}
	exit (0);
}
