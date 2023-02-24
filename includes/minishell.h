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

#define SQUOTE 39
#define DQUOTE 34
#define DOLLAR 36
#define TILDE 126
#define YELLOW "\033[1;33m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define PURPLE "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"
#define RESET "\033[0m"

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

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_minishell
{
	char		**paths;

	t_cmdlist	*cmds;
	t_env		*head_env;

	char		**envp;
	char		**argv;
	int			argc;

	int			end[2];
}				t_minishell;

char		**ft_pathfinder(t_env **head);
char		**ft_strsdup(char **strs);
char		**ft_expand_var(t_env **head, char **cmds);
void		ft_parse_env(t_env **head, char **envp);
char		**ft_expand_path(t_env **head, char **cmds);


t_cmdlist	*ft_cmdlist(char *cmd_line, t_minishell *data);
void		ft_print_cmdlist(t_cmdlist *cmds);

void		pipex(t_minishell *data);
void		exec_cmd(t_minishell *data, char *buffer);

#endif
