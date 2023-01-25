#include "../includes/minishell.h"

void	ft_cd(char *path)
{
	if (chdir(path) == -1)
		perror("chdir()");
}

void	ft__pwd(void)
{
	char cwd[PATH_MAX];
	
	if (getcwd(cwd, sizeof(cwd)))
	    	printf("%s\n", cwd);
	else 
		perror("getcwd()");
}

int	ft_built_ins(data, buffer);
{
	const char	*built_ins[] = {"pwd", "cd", NULL};
	int	i;

	i = -1;
	while (built_ins[++i])
		if (!strcmp(built_ins[i], buffer))
			return (1);
	return (0);
}


