/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:19:13 by zrebhi            #+#    #+#             */
/*   Updated: 2023/01/17 14:13:54 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	data_init(t_pipex *data, int argc, char **argv, char **envp)
{
	data->children = malloc(sizeof(int) * (argc - 3));
	if (!data->children)
		return (perror("malloc children"), exit (1));
	data->no_problem = 0;
	data->paths = ft_pathfinder(envp);
	data->env = envp;
	data->argv = argv;
	data->argc = argc;
	data->fd_infile = open(argv[1], O_RDONLY);
	if (data->fd_infile == -1)
		perror("open infile");
	data->fd_outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_outfile == -1)
		perror("open outfile");
}

void	ft_free_all(t_pipex *data)
{
	int	i;

	i = -1;
	if (data->paths)
	{
		while (data->paths[++i])
			free(data->paths[i]);
		free(data->paths);
	}
	i = -1;
	if (data->cmds)
	{
		while (data->cmds[++i])
			free(data->cmds[i]);
		free(data->cmds);
	}
	free(data->children);
	if (data->heredoc == 0)
		if (data->fd_infile != -1 && close(data->fd_infile) == -1)
			perror("close infile");
	if (close(data->fd_outfile != -1 && data->fd_outfile == -1))
		perror("close outfile");
	exit (1);
}

void	ft_free_paths(t_pipex *data)
{
	int	i;

	i = -1;
	if (data->paths)
	{
		while (data->paths[++i])
			free(data->paths[i]);
		free(data->paths);
	}
	free(data->children);
	if (data->heredoc == 0)
		if (data->fd_infile != -1 && close(data->fd_infile) == -1)
			perror("close infile");
	if (data->fd_outfile != -1 && close(data->fd_outfile == -1))
		perror("close outfile");
	if (data->no_problem == 1)
		return ;
	exit (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc < 5)
		return (ft_putstr_fd("Incorrect number of arguments.\n", 2), 1);
	data.heredoc = 0;
	if (!ft_strcmp(argv[1], "here_doc"))
	{
		heredoc_init(&data, argc, argv, envp);
		heredoc(&data);
	}
	if (data.heredoc == 0)
		data_init(&data, argc, argv, envp);
	pipex(&data);
	data.no_problem = 1;
	ft_free_paths(&data);
	return (0);
}
