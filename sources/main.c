#include "../includes/minishell.h"

void	data_init(int argc, char **argv, char **envp, t_minishell *data)
{
	data->paths = ft_pathfinder(envp);
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
}

void    ft_prompt(t_minishell *data)
{
    char    	*buffer;
    int         status;
    int         pid;

    while (1) 
    {
        buffer = readline("minishell > ");
        if (!buffer)
            break ; 
        data->cmds = ft_cmdlist(buffer);
        pid = fork();
        if (pid == 0)
            pipex(data);
        waitpid(pid, &status, 0);
        printf("\n");
    }
    printf("Ciao, Bye !");
}

int    main(int argc, char **argv, char **envp)
{
    t_minishell data;

    data_init(argc, argv, envp, &data);
    ft_prompt(&data);
    return (0);
}
