/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:14:39 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/28 02:53:32 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	_string_length(char **cmd, char *quote);
static char	*_make_string(char *res_cmd, char *copy_address, int len);
static int	_is_quote(char q, char *tmp_quote);

char	*remove_quotation(char *command, int origin_len)
{
	char	*res_cmd;
	char	*origin;
	char	*copy_address;
	char	quote;
	int		len;

	origin = command;
	res_cmd = NULL;
	while (*command)
	{
		copy_address = command;
		len = _string_length(&command, &quote);
		if (len == origin_len)
			return (origin);
		if (quote != 0)
			copy_address++;
		res_cmd = _make_string(res_cmd, copy_address, len);
	}
	free (origin);
	return (res_cmd);
}

static int	_string_length(char **cmd, char *quote)
{
	int		len;

	len = 0;
	*quote = 0;
	if (_is_quote(**cmd, quote) == TRUE)
	{
		while (*(++(*cmd)) != *quote && ++len)
			if (**cmd == 0)
				exit (EXIT_FAILURE);
		(*cmd)++;
	}
	else
	{
		while (**cmd && _is_quote(**cmd, quote) == FALSE && ++len)
			(*cmd)++;
		*quote = 0;
	}
	return (len);
}

static char	*_make_string(char *res_cmd, char *copy_address, int len)
{
	char	*new_string;
	char	*_add;

	_add = ft_calloc(len + 1, sizeof(char));
	if (_add == NULL)
		exit (EXIT_FAILURE);
	ft_strlcpy(_add, copy_address, len + 1);
	if (res_cmd == NULL)
		return (_add);
	new_string = ft_strjoin(res_cmd, _add);
	if (new_string == NULL)
		exit (EXIT_FAILURE);
	free (res_cmd);
	free (_add);
	return (new_string);
}

static int	_is_quote(char q, char *tmp_quote)
{
	if (q == '\'' || q == '\"')
	{
		*tmp_quote = q;
		return (TRUE);
	}
	return (FALSE);
}
