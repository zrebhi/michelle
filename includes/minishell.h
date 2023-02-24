#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/includes/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

#ifndef PATH_MAX
# define PATH_MAX 1024
#endif

typedef int	t_pid;

typedef struct s_cmdlist
{
	char            	**full_cmd;
	int             	infile;
	int	            	outfile;
	int					here_doc;
	char				*limiter;
	t_pid				cmd_pid;
    struct s_cmdlist	*next;
}		   			 	t_cmdlist;

typedef struct s_minishell
{
	char		**paths;

	t_cmdlist	*cmds;

	char		**envp;
	char		**argv;
	int			argc;

	int			end[2];
}				t_minishell;

char		**ft_pathfinder(char **envp);

char		**ft_cmd_args(char *cmd);

void		exec_cmd(t_minishell *data, char *buffer);

t_cmdlist	*ft_cmdlist(char *cmd_line);

void		ft_print_cmdlist(t_cmdlist *cmds);

void		pipex(t_minishell *data);

#endif
