/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:49:59 by zrebhi            #+#    #+#             */
/*   Updated: 2022/11/15 15:50:00 by zrebhi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nblen(int n)
{
	int				len;
	unsigned int	num;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
	{
		num = -n;
		len++;
	}
	else
		num = n;
	while (num > 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*a;
	int				i;
	unsigned int	num;

	a = malloc(ft_nblen(n) + 1);
	if (!a)
		return (0);
	if (n == 0)
		a[0] = '0';
	i = 0;
	if (n < 0)
	{
		a[0] = '-';
		num = -n;
	}
	else
		num = n;
	while (num > 0)
	{
		a[ft_nblen(n) - i++ - 1] = num % 10 + '0';
		num = num / 10;
	}
	a[ft_nblen(n)] = 0;
	return (a);
}
