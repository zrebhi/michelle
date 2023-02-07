/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:38:12 by zrebhi            #+#    #+#             */
/*   Updated: 2023/01/17 13:57:07 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str2[i] && str1[i] == str2[i])
			i++;
	if (str1[i] - str2[i] > 0)
		return (1);
	if (str1[i] - str2[i] == 0)
		return (0);
	if (str1[i] - str2[i] < 0)
		return (-1);
	return (0);
}
