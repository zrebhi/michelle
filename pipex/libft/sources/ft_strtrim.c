/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:03:01 by zrebhi            #+#    #+#             */
/*   Updated: 2022/11/15 14:03:05 by zrebhi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char const *set, char c)
{
	int	i;

	i = 0;
	if (c == 0)
		return (1);
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] && ft_check(set, s1[i]) == 1)
		i++;
	return (i);
}

static int	ft_end(char const *s1, char const *set, int start)
{
	int	j;

	j = 0;
	while (s1[j])
		j++;
	while (j > start && ft_check(set, s1[j]) == 1)
		j--;
	if (j == 0)
		return (start);
	return (j + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strim;
	int		start;
	int		end;
	int		i;

	if (!s1)
		return (0);
	start = ft_start(s1, set);
	end = ft_end(s1, set, start);
	strim = malloc(sizeof(char) * (end - start + 1));
	if (!strim)
		return (0);
	strim[0] = 0;
	i = 0;
	if (end == 0)
		return (strim);
	while (s1[start] && start < end)
	{
		strim[i] = s1[start];
		i++;
		start++;
	}
	strim[i] = 0;
	return (strim);
}
