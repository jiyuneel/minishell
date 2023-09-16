/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_by_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 08:51:54 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/16 14:56:09 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*token_new_node(t_token_type type, char *value)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = value;
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

void	parse_by_pipe(t_token **token, char *str)
{
	static t_quote	q;
	char			*tmp;
	char			*value;

	tmp = str;
	while (1)
	{
		check_quote(&q.quote_flag, &q.quote, *str);
		if (!q.quote_flag && (!*str || *str == '|'))
		{
			if (str != tmp)
			{
				value = malloc(sizeof(char) * (str - tmp + 1));
				ft_strlcpy(value, tmp, str - tmp + 1);
				token_add_back(token, token_new_node(STR, value));
			}
			if (*str++ == '|')
				token_add_back(token, token_new_node(PIPE, ft_strdup("|")));
			else
				break ;
			tmp = str;
		}
		else
			str++;
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
