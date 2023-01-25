/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:31:21 by zrebhi            #+#    #+#             */
/*   Updated: 2023/01/17 14:01:25 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	heredoc_init(t_pipex *data, int argc, char **argv, char **envp)
{
	data->children = malloc(sizeof(int) * (argc - 4));
	if (!data->children)
		return (perror("malloc children"), exit (1));
	data->no_problem = 0;
	data->heredoc = 1;
	data->paths = ft_pathfinder(envp);
	data->env = envp;
	data->argv = argv;
	data->argc = argc;
	data->fd_outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | \
			O_APPEND, 0644);
	if (data->fd_outfile == -1)
		perror("open outfile");
}

static void	ft_input(t_pipex *data)
{
	size_t	length;
	char	*line;

	while (1)
	{
		ft_putstr_fd("pipex here_doc> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (ft_free_paths(data));
		if (ft_strlen(line) - 1 > ft_strlen(data->argv[2]))
			length = ft_strlen(line) - 1;
		else
			length = ft_strlen(data->argv[2]);
		if (!ft_strncmp(line, data->argv[2], length))
		{
			if (close(data->end[0]) == -1 || close(data->end[1]) == -1)
				return (perror("close pipe"), ft_free_paths(data));
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, data->end[1]);
		free(line);
	}
}

void	heredoc(t_pipex *data)
{
	pid_t	heredoc_pid;

	if (data->argc < 6)
		return (ft_putstr_fd("Invalid number of arguments.\n", 2), \
				ft_free_paths(data));
	if (pipe(data->end) == -1)
		return (perror("heredoc pipe"), ft_free_paths(data));
	heredoc_pid = fork();
	if (heredoc_pid == -1)
		return (perror("heredoc fork"), ft_free_paths(data));
	if (heredoc_pid == 0)
		ft_input(data);
	waitpid(heredoc_pid, NULL, 0);
	dup2(data->end[0], STDIN_FILENO);
	if (close(data->end[0]) == -1 || close(data->end[1]) == -1)
		return (perror("close pipe"), ft_free_paths(data));
}
