/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:02:59 by zrebhi            #+#    #+#             */
/*   Updated: 2023/02/23 17:08:12 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	data_init(int argc, char **argv, char **envp, t_minishell *data)
{
	data->paths = ft_pathfinder(envp);
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
}

void	ft_prompt(t_minishell *data)
{
	char		*buffer;
	int			status;
	int			pid;

	while (1)
	{
		buffer = readline("minishell > ");
		if (!buffer)
			break ;
		add_history(buffer);
		data->cmds = ft_cmdlist(buffer);
		ft_print_cmdlist(data->cmds);
		pid = fork();
		if (pid == 0)
			pipex(data);
		waitpid(pid, &status, 0);
	}
	printf("Ciao, Bye !");
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;

	data_init(argc, argv, envp, &data);
	ft_prompt(&data);
	return (0);
}
