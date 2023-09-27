/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:55:48 by jiyunlee          #+#    #+#             */
/*   Updated: 2022/11/15 20:29:21 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	size;
	int	i;

	size = ft_lstsize(lst);
	i = 0;
	while (i++ < size - 1)
		lst = lst->next;
	return (lst);
}
