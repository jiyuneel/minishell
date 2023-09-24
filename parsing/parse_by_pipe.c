/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_by_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 08:51:54 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/24 22:09:42 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_by_pipe(t_token **token, char *str)
{
	t_quote	q;
	char	*tmp;
	char	*value;

	q.quote_flag = FALSE;
	tmp = str;
	while (1)
	{
		if (!check_quote(&q, *str) && (!*str || *str == '|'))
		{
			if (str != tmp)
			{
				value = ft_strndup(tmp, str - tmp);
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
