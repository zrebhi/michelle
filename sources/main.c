/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:02:59 by zrebhi            #+#    #+#             */
/*   Updated: 2023/02/24 20:26:10 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	data_init(int argc, char **argv, char **envp, t_minishell *data)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	ft_parse_env(&data->head_env, data->envp);
	data->paths = ft_pathfinder(&data->head_env);
}

static char    *get_prompt(t_env *head, char *key)
{
    t_env	*temp;

    temp = head;
    while (temp)
    {
        if (ft_strcmp(temp->key, key) == 0)
            return (ft_strjoin(ft_strjoin(""GREEN"➜  "CYAN"", temp->value),
				""PURPLE"@minishell > "RESET""));
        temp = temp->next;
    }
    return (""GREEN"➜  "CYAN"guest"PURPLE"@minishell > "RESET"");
}

void	ft_prompt(t_minishell *data)
{
	char		*buffer;
	int			status;
	int			pid;
	char        *prompt;

    prompt = get_prompt(data->head_env, "USER");
	while (1)
	{
		buffer = readline(prompt);
		if (!buffer)
			break ;
		add_history(buffer);
		data->cmds = ft_cmdlist(buffer, data);
//		ft_print_cmdlist(data->cmds);
		pid = fork();
		if (pid == 0)
			pipex(data);
		waitpid(pid, &status, 0);
	}
	printf("Ciao, Bye !");
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;
	
	data_init(argc, argv, envp, &data);
	ft_prompt(&data);
	return (0);
}
