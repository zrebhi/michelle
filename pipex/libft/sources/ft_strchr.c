/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:37:53 by zrebhi            #+#    #+#             */
/*   Updated: 2022/11/10 11:37:56 by zrebhi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;
	char	c2;

	str = (char *)s;
	c2 = c;
	i = 0;
	while (str[i])
	{
		if (str[i] == c2)
			return (&str[i]);
		i++;
	}
	if (c2 == 0)
		return (&str[i]);
	else
		return (0);
}
