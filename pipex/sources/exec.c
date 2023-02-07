/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:17:49 by zrebhi            #+#    #+#             */
/*   Updated: 2023/01/17 13:49:57 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/* Handles the executions of the commands and returns the corresponding error
if the command was not found. */

void	ft_exec(t_pipex *data)
{
	int		i;
	char	*cmd;

	i = -1;
	if (data->cmds)
	{
		execve(data->cmds[0], data->cmds, data->env);
		if (data->paths)
		{
			while (data->paths[++i])
			{
				cmd = ft_strjoin(data->paths[i], data->cmds[0]);
				if (!cmd)
					return ;
				execve(cmd, data->cmds, data->env);
				free(cmd);
			}
		}
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(data->cmds[0], 2);
		ft_putstr_fd("\n", 2);
		return ;
	}
	ft_putstr_fd("command not found: \n", 2);
}

/* Handles everything related to children processes. */

void	ft_incubator(t_pipex *data, int i)
{
	if (close(data->end[0]) == -1)
		return (perror("close pipe"), ft_free_paths(data));
	if (i == 0 && data->heredoc == 0)
	{
		if (dup2(data->fd_infile, STDIN_FILENO) == -1)
		{
			if (data->fd_infile != -1)
				perror("dup2 infile");
			return (ft_free_paths(data));
		}
	}
	if (i == data->argc - 4 - data->heredoc)
	{
		if (dup2(data->fd_outfile, STDOUT_FILENO) == -1)
		{
			if (data->fd_outfile != -1)
				perror("dup2 infile");
			return (ft_free_paths(data));
		}
	}
	else if (dup2(data->end[1], STDOUT_FILENO) == -1)
		return (perror("dup2 end[1]"), ft_free_paths(data));
	data->cmds = ft_cmd_args(data->argv[i + 2 + data->heredoc]);
	ft_exec(data);
	return (ft_free_all(data));
}

/* Creates a child process for every command and links them together
with pipes */

void	pipex(t_pipex *data)
{
	int	status;
	int	i;

	i = -1;
	while (++i < data->argc - 3 - data->heredoc)
	{
		if (pipe(data->end) == -1)
			return (perror("pipe"), ft_free_paths(data));
		data->children[i] = fork();
		if (data->children[i] == -1)
			return (perror("Fork"), ft_free_paths(data));
		if (data->children[i] == 0)
			ft_incubator(data, i);
		if (dup2(data->end[0], STDIN_FILENO) == -1)
			return (perror("dup2 end[0]"), ft_free_paths(data));
		if (close(data->end[0]) == -1 || close(data->end[1]) == -1)
			return (perror("close pipe"), ft_free_paths(data));
	}
	if (data->fd_outfile != -1 && close(data->fd_outfile) == -1)
		perror("close outfile");
	i = -1;
	while (++i < data->argc - 3 - data->heredoc)
		waitpid(data->children[i], &status, 0);
}
