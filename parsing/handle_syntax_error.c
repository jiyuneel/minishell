/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syntax_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 23:36:46 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/18 00:57:28 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	syntax_error_quote(char *str);
int	syntax_error_token(t_token *token);

int	handle_syntax_error(t_token *token, char *str)
{
	if (!token)
		return (syntax_error_quote(str));
	else
		return (syntax_error_token(token));
}

int	print_syntax_error(char *str)
{
	printf("jijishell: syntax error near unexpected token `%s\'\n", str);
	return (EXIT_FAILURE);
}

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
		if (q.quote == '\'')
			return (print_syntax_error("'"));
		else if (q.quote == '\"')
			return (print_syntax_error("\""));
	}
	return (EXIT_SUCCESS);
}

int	syntax_error_token(t_token *token)
{
	t_token	*tmp;

	if (token->type == PIPE)
		return (print_syntax_error(token->value));
	tmp = token;
	while (tmp->next)
	{
		if (((LEFT_1 <= tmp->type && tmp->type <= RIGHT_2) && tmp->next->type != STR)
			|| (tmp->type == PIPE && tmp->next->type == PIPE))
			return (print_syntax_error(tmp->next->value));
		tmp = tmp->next;
	}
	if (tmp)
	{
		if (LEFT_1 <= tmp->type && tmp->type <= RIGHT_2)
			return (print_syntax_error("newline"));
		else if (tmp->type == PIPE)
			return (print_syntax_error(tmp->value));
	}
	return (EXIT_SUCCESS);
}
