/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:52:48 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/19 11:53:22 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env_info	*env_new_node(char *key, char *value)
{
	t_env_info	*node;

	node = ft_calloc(1, sizeof(t_env_info));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	env_add_back(t_env_info **node, t_env_info *new)
{
	t_env_info	*tmp;

	if (!(*node))
		*node = new;
	else
	{
		tmp = *node;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	env_add_front(t_env_info **node, t_env_info *new)
{
	new->next = *node;
	*node = new;
}
