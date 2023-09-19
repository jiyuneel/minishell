/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:07:25 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/19 18:00:16 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*token_new_node(t_token_type type, char *value)
{
	t_token	*node;

	node = ft_calloc(1, sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = value;
	node->valid = TRUE;
	node->next = NULL;
	return (node);
}

void	token_add_back(t_token **node, t_token *new)
{
	t_token	*tmp;

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

void	free_token(t_token *token)
{
	t_token	*tmp;

	if (token == NULL)
		return ;
	while (token)
	{
		tmp = token->next;
		free (token->value);
		free (token);
		token = tmp;
	}
}
