#include "../includes/minishell.h"

void	data_init(int argc, char **argv, char **envp, t_minishell *data)
{
	data->paths = ft_pathfinder(envp);
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
}

char	*ft_remove_newline(char *buffer)
{
	int	i;
	int	len;
	char *no_line;

	len = ft_strlen(buffer);
	no_line = malloc(sizeof(char) * len);
	i = -1;
	while (buffer[++i] != '\n')
		no_line[i] = buffer[i];
	no_line[i] = 0;
	free(buffer);
	return (no_line);
}

void	ft_prompt(t_minishell *data)
{
	char	*buffer;

	write(1, "michelle$> ", 11);
	while (1) 
	{
		buffer = get_next_line(STDIN_FILENO);
		buffer = ft_remove_newline(buffer);
		if (!buffer)
			break ;
		exec_cmd(data, buffer);
		write(1, "michelle$> ", 11);
	}
	ft_putstr_fd("Ciao, Bye !\n", 1);
	free(buffer);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;

	data_init(argc, argv, envp, &data);
	ft_prompt(&data);
	return (0);
}
