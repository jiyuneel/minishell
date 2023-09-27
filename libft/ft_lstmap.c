/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:55:58 by jiyunlee          #+#    #+#             */
/*   Updated: 2022/11/21 15:11:00 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*node;
	void	*ptr;

	if (!lst)
		return (NULL);
	newlst = 0;
	while (lst)
	{
		ptr = (*f)(lst->content);
		node = ft_lstnew(ptr);
		if (!node)
		{
			ft_lstclear(&newlst, (*del));
			del(ptr);
			return (NULL);
		}
		ft_lstadd_back(&newlst, node);
		lst = lst->next;
	}
	return (newlst);
}
