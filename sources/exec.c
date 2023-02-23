/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:17:49 by zrebhi            #+#    #+#             */
/*   Updated: 2023/02/23 12:33:51 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

/* Handles everything related to children processes. */

void	ft_incubator(t_minishell *data)
{
	if (close(data->end[0]) == -1)
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
	ft_exec(data);
	return ;
}

/* Creates a child process for every command and links them together
with pipes */

void	pipex_commands(t_minishell *data)
{
	while (data->cmds)
	{
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
	exit (1);
}
