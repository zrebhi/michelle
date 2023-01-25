#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/includes/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef PATH_MAX
# define PATH_MAX 1024
#endif

typedef int	t_pid;

typedef struct s_minishell
{
	char	**paths;

	char	**cmds;

	char	**envp;
	char	**argv;
	int		argc;

	int		fd_infile;
	int		fd_outfile;

	int		end[2];
	t_pid	*children;
}			t_minishell;

char	**ft_pathfinder(char **envp);

char	**ft_cmd_args(char *cmd);

void	exec_cmd(t_minishell *data, char *buffer);

#endif
