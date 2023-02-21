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
    char    	*buffer = NULL;

    while (1) 
    {
        buffer = readline("Oui Michelle ?$> ");
        if (!buffer)
            break;
		data->cmds = ft_cmdlist(buffer);
        pipex(data);
        printf("\n");
    }
    printf("Nique ton oncle !");
}

int    main(int argc, char **argv, char **envp)
{
    t_minishell data;

    data_init(argc, argv, envp, &data);
    ft_prompt(&data);
    pipex(&data);
    return (0);
}
