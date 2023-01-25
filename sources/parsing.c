/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:18:32 by zrebhi            #+#    #+#             */
/*   Updated: 2023/01/24 15:53:33 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Retrieves the different paths from the environment */

char	**ft_pathfinder(char **envp)
{
	char	*paths_line;
	char	**paths;
	int		i;

	i = 0;
	if (!envp[0] || !envp)
		return (0);
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (0);
	paths_line = envp[i] + 5;
	paths = ft_split_slash(paths_line, ':');
	return (paths);
}

/* Retrieves the command and its args and stores it in a char **.
If there are args, the command and its args MUST be between quotes
(i.e ls, "ls -a"). */

char	**ft_cmd_args(char *cmd)
{
	char	**cmds;
	
	if (!cmd[0])
		return (0);
	cmds = ft_split(cmd, ' ');
	return (cmds);
}
