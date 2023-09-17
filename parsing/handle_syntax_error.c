/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syntax_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 23:36:46 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/17 15:34:04 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_quote(int *quote_flag, char *quote, char c)
{
	if (!*quote_flag && (c == '\'' || c == '\"'))
	{
		*quote_flag = TRUE;
		*quote = c;
	}
	else if (*quote_flag && c == *quote)
		*quote_flag = FALSE;
}

int	syntax_error_quote(char *str)
{
	t_quote	q;

	q.quote_flag = FALSE;
	while (*str)
	{
		check_quote(&q.quote_flag, &q.quote, *str);
		str++;
	}
	if (q.quote_flag)
	{
		printf("jijishell: syntax error near unexpected token `%c\'\n", q.quote);
		return (EXIT_FAILURE);
	}
	else
		return (EXIT_SUCCESS);
}

int	syntax_error_token(t_token *token)
{}

int	handle_syntax_error(t_token *token, char *str)
{
	if (!token)
		return (syntax_error_quote(str));
	else
	{
		
	}
	return (EXIT_SUCCESS);
}
