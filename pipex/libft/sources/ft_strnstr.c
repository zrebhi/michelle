/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:23:25 by zrebhi            #+#    #+#             */
/*   Updated: 2022/11/24 10:49:07 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)

{
	size_t	i;
	size_t	j;

	if (len == 0 && haystack == 0)
		return (0);
	if (needle[0] == 0)
		return ((char *)haystack);
	i = 0;
	j = 0;
	while (haystack[i] && i <= len)
	{
		if (needle[j] && haystack[i + j] && haystack[i + j] == needle[j])
			j++;
		else
		{
			if (!needle[j] && i + j <= len)
				return ((char *)haystack + i);
			j = 0;
			i++;
		}
	}
	return (0);
}
