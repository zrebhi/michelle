/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:38:12 by zrebhi            #+#    #+#             */
/*   Updated: 2022/11/17 12:14:10 by zrebhi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (str2[i] && str1[i] == str2[i] && i < n - 1)
			i++;
	if (str1[i] - str2[i] > 0)
		return (1);
	if (str1[i] - str2[i] == 0)
		return (0);
	if (str1[i] - str2[i] < 0)
		return (-1);
	return (0);
}
