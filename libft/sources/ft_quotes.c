/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:45:19 by zrebhi            #+#    #+#             */
/*   Updated: 2023/02/07 16:49:50 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_quotes(char const *s, int *j)
{
	if (s[(*j)] == '"')
	{
		(*j)++;
		while (s[(*j)] && s[(*j)] != '"')
			(*j)++;
	}
	else if (s[(*j)] == '\'')
	{
		(*j)++;
		while (s[(*j)] && s[(*j)] != '\'')
			(*j)++;
	}
}
