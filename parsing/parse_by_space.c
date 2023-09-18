/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_by_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:28:16 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/18 15:39:38 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

int	token_len(char *str)
{
	int		len;
	t_quote	q;

	len = 0;
	q.quote_flag = FALSE;
	while (*str)
	{
		check_quote(&q.quote_flag, &q.quote, *str);
		if (!q.quote_flag && *str == ' ')
			break ;
		len++;
		str++;
	}
	return (len);
}

t_token	*_parse_by_space(char *str)
{
	t_token	*token;
	char	*value;
	int		len;

	token = NULL;
	while (*str)
	{
		if (*str != ' ')
		{
			len = token_len(str);
			value = malloc(sizeof(char) * (len + 1));
			ft_strlcpy(value, str, len + 1);
			token_add_back(&token, token_new_node(STR, value));
			str += len;
		}
		else
			str++;
	}
	return (token);
}

void	parse_by_space(t_token **token)
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
			new_nodes = _parse_by_space(tmp->value);
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
