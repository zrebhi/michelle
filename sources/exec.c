/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:17:49 by zrebhi            #+#    #+#             */
/*   Updated: 2023/01/25 13:40:10 by zrebhi           ###   ########.fr       */
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
	if (data->cmds)
	{
		execve(data->cmds[0], data->cmds, data->envp);
		if (data->paths)
		{
			while (data->paths[++i])
			{
				cmd = ft_strjoin(data->paths[i], data->cmds[0]);
				if (!cmd)
					return ;
				execve(cmd, data->cmds, data->envp);
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

void	exec_cmd(t_minishell *data, char *buffer)
{
	pid_t	pid = 0;
	int		status = 0;


	pid = fork();
	if (pid == -1)
		perror("fork");
	// Si le fork a reussit, le processus pere attend l'enfant (process fork)
	else if (pid > 0) 
		waitpid(pid, &status, 0);
	else
	{
		data->cmds = ft_cmd_args(buffer);
		ft_exec(data);
		exit(EXIT_FAILURE);
	}
}
