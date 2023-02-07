/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:30:29 by zrebhi            #+#    #+#             */
/*   Updated: 2022/11/24 10:40:11 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstnew_free(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(*new));
	if (!new)
	{
		free(content);
		return (0);
	}
	new->content = content;
	new->next = 0;
	return (new);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*temp;

	map = 0;
	while (lst)
	{
		temp = ft_lstnew_free(f(lst->content));
		if (!temp)
		{
			ft_lstclear(&map, del);
			return (map);
		}
		ft_lstadd_back(&map, temp);
		lst = lst->next;
	}
	return (map);
}
