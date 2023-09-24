/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_by_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:21:05 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/24 22:23:54 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	_parse_by_redir(t_token **token, char *str)
{
	t_quote	q;
	char	*tmp;

	q.quote_flag = FALSE;
	tmp = str;
	while (*str)
	{
		if (!check_quote(&q, *str) && (*str == '<' || *str == '>'))
		{
			if (str != tmp)
				token_add_back(token, \
					token_new_node(STR, ft_strndup(tmp, str - tmp)));
			if ((*str == '<' && *(str + 1) != '<') && str++)
				token_add_back(token, token_new_node(LEFT_1, ft_strdup("<")));
			else if ((*str == '<' && *(str + 1) == '<') && str++ && str++)
				token_add_back(token, token_new_node(LEFT_2, ft_strdup("<<")));
			else if (*str == '>' && *(str + 1) != '>' && str++)
				token_add_back(token, token_new_node(RIGHT_1, ft_strdup(">")));
			else if (*str == '>' && *(str + 1) == '>' && str++ && str++)
				token_add_back(token, token_new_node(RIGHT_2, ft_strdup(">>")));
			tmp = str--;
		}
		str++;
	}
	token_add_back(token, token_new_node(STR, ft_strndup(tmp, str - tmp)));
}

void	parse_by_redir(t_token **token)
{
	t_token	*tmp;
	t_token	*tmp_next;
	t_token	*new_nodes;

	tmp = *token;
	while (tmp)
	{
		if (tmp->valid && tmp->type == STR)
		{
			tmp_next = tmp->next;
			new_nodes = NULL;
			_parse_by_redir(&new_nodes, tmp->value);
			if (new_nodes)
				tmp->valid = FALSE;
			tmp->next = new_nodes;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = tmp_next;
		}
		tmp = tmp->next;
	}
}
