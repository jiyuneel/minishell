/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syntax_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 23:36:46 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/24 22:53:55 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	syntax_error_quote(char *str);
int	syntax_error_token(t_token *token);

int	handle_syntax_error(t_shell_info *shell_info, t_token *token, char *str)
{
	t_token	*tmp = token;

	if (!token)
		return (syntax_error_quote(str));
	else
	{
		while (tmp)
		{
			if (tmp->type == LEFT_2)
				shell_info->heredoc_cnt++;
			if (shell_info->heredoc_cnt > 16)
			{
				printf("jijishell: maximum here-document count exceeded\n");
				exit(1);
			}
			tmp = tmp->next;
		}
		return (syntax_error_token(token));
	}
}

int	print_syntax_error(char *str)
{
	printf("jijishell: syntax error near unexpected token `%s\'\n", str);
	g_exit_code = 258;
	return (EXIT_FAILURE);
}

int	check_quote(t_quote	*q, char c)
{
	if (!q->quote_flag && (c == '\'' || c == '\"'))
	{
		q->quote_flag = TRUE;
		q->quote = c;
	}
	else if (q->quote_flag && c == q->quote)
		q->quote_flag = FALSE;
	return (q->quote_flag);
}

int	syntax_error_quote(char *str)
{
	t_quote	q;

	q.quote_flag = FALSE;
	while (*str)
	{
		check_quote(&q, *str);
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
