/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redir_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 21:18:25 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/19 18:25:17 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redir	*redir_new_node(t_token_type type, char *filename)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->type = type;
	node->filename = filename;
	node->next = NULL;
	return (node);
}

void	redir_add_back(t_redir **node, t_redir *new)
{
	t_redir	*tmp;

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

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	if (redir == NULL)
		return ;
	while (redir)
	{
		tmp = redir->next;
		free (redir->filename);
		free (redir);
		redir = tmp;
	}
}
