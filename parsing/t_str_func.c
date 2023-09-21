/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_str_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 21:11:12 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/19 18:00:09 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_str	*str_new_node(char *command)
{
	t_str	*node;

	node = malloc(sizeof(t_str));
	if (!node)
		return (NULL);
	node->type = STR;
	node->command = command;
	node->next = NULL;
	return (node);
}

void	str_add_back(t_str **node, t_str *new)
{
	t_str	*tmp;

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

void	free_str(t_str *str)
{
	t_str	*tmp;

	if (str == NULL)
		return ;
	while (str)
	{
		tmp = str->next;
		free (str->command);
		free (str);
		str = tmp;
	}
}
