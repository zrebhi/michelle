/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:42:32 by zrebhi            #+#    #+#             */
/*   Updated: 2022/11/14 21:38:35 by zrebhi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strsize(const char *str, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (str[i] && i < dstsize)
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstlen;

	if (dstsize == 0)
		return (ft_strlen(src));
	dstlen = ft_strsize(dst, dstsize);
	if (dstlen >= dstsize)
		return (dstsize + ft_strlen(src));
	i = 0;
	while (src[i] && dstlen + i < dstsize - 1)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = 0;
	return (dstlen + ft_strlen(src));
}
