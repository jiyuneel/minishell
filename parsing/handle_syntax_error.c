/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syntax_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 23:36:46 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/29 14:25:12 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	syntax_error_quote(char *str);
int	syntax_error_token(t_token *token);

int	handle_syntax_error(t_shell_info *shell_info, t_token *token, char *str)
{
	t_token	*tmp;

	tmp = token;
	if (!token)
		return (syntax_error_quote(str));
	else
	{
		while (tmp)
		{
			if (tmp->type == HRD)
				shell_info->heredoc_cnt++;
			if (shell_info->heredoc_cnt > 16)
			{
				error_message(NULL, NULL, \
					"maximum here-document count exceeded");
				set_origin_exit(shell_info->origin_term, 1, FALSE);
			}
			tmp = tmp->next;
		}
		return (syntax_error_token(token));
	}
}

int	print_syntax_error(char *str)
{
	ft_putstr_fd("jijishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\'\n", 2);
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
		if (((IRD <= tmp->type && tmp->type <= ARD) && tmp->next->type != STR)
			|| (tmp->type == PIPE && tmp->next->type == PIPE))
			return (print_syntax_error(tmp->next->value));
		tmp = tmp->next;
	}
	if (tmp)
	{
		if (IRD <= tmp->type && tmp->type <= ARD)
			return (print_syntax_error("newline"));
		else if (tmp->type == PIPE)
			return (print_syntax_error(tmp->value));
	}
	return (EXIT_SUCCESS);
}
