/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_by_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:21:05 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/16 18:27:00 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	redir_exist(char *str)
{
	static t_quote	q;

	while (*str)
	{
		check_quote(&q.quote_flag, &q.quote, *str);
		if (!q.quote_flag && (*str == '<' || *str == '>'))
			return (TRUE);
		str++;
	}
	return (FALSE);
}

t_token	*_parse_by_redir(char *str)
{
	static t_quote	q;
	char			*tmp;
	int				redir_flag;
	t_token			*token;
	char			*value;

	token = NULL;
	redir_flag = redir_exist(str);
	tmp = str;
	while (redir_flag)
	{
		check_quote(&q.quote_flag, &q.quote, *str);
		if (!q.quote_flag && (!*str || *str == '<' || *str == '>'))
		{
			if (str != tmp)
			{
				value = malloc(sizeof(char) * (str - tmp + 1));
				ft_strlcpy(value, tmp, str - tmp + 1);
				token_add_back(&token, token_new_node(STR, value));
			}
			if (*str == '<' && *(str + 1) != '<')
			{
				token_add_back(&token, token_new_node(LEFT_1, ft_strdup("<")));
				str += 1;
			}
			else if (*str == '<' && *(str + 1) == '<')
			{
				token_add_back(&token, token_new_node(LEFT_2, ft_strdup("<<")));
				str += 2;
			}
			else if (*str == '>' && *(str + 1) != '>')
			{
				token_add_back(&token, token_new_node(RIGHT_1, ft_strdup(">")));
				str += 1;
			}
			else if (*str == '>' && *(str + 1) == '>')
			{
				token_add_back(&token, token_new_node(RIGHT_2, ft_strdup(">>")));
				str += 2;
			}
			else
				break ;
			tmp = str;
		}
		else
			str++;
	}
	return (token);
}

void	parse_by_redir(t_token **token)
{
	t_token	*tmp;
	t_token	*tmp_next;
	t_token	*new_nodes;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == STR)
		{
			tmp_next = tmp->next;
			new_nodes = _parse_by_redir(tmp->value);
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
