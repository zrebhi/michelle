/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:17:18 by zrebhi            #+#    #+#             */
/*   Updated: 2023/01/13 18:06:15 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/includes/libft.h"

typedef int	t_pid;

typedef struct s_pipex
{
	char	**paths;

	char	**cmds;

	int		fd_infile;
	int		fd_outfile;

	int		end[2];
	t_pid	*children;

	char	**env;
	char	**argv;
	int		argc;

	int		no_problem;
	int		heredoc;
}			t_pipex;

char	**ft_pathfinder(char **envp);

char	**ft_cmd_args(char *argv);

void	pipex(t_pipex *data);

void	ft_free_all(t_pipex *data);

void	ft_free_paths(t_pipex *data);

void	heredoc(t_pipex *data);

void	heredoc_init(t_pipex *data, int argc, char **argv, char **envp);

#endif