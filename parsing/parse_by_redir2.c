/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_by_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:00:11 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/16 14:12:30 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_redir_str(char *str)
{
	int		cnt;
	t_quote	q;

	cnt = 0;
	q.quote_flag = FALSE;
	while (*str)
	{
		check_quote(&q.quote_flag, &q.quote, *str);
		if (!q.quote_flag && (*str != '<' && *str != '>'))
		{
			cnt++;
			while (*str && (*str != '<' && *str != '>'))
				str++;
		}
		else if (!q.quote_flag && (*str == '<' || *str == '>'))
		{
			cnt++;
			while (*str && (*str == '<' || *str == '>'))
				str++;
		}
		else
			str++;
	}
	return (cnt);
}

int	redir_str_len(char *str)
{
	char	*tmp;
	t_quote	q;

	tmp = str;
	q.quote_flag = FALSE;
	while (*str)
	{
		check_quote(&q.quote_flag, &q.quote, *str);
		if (!q.quote_flag && (*str != '<' && *str != '>'))
		{
			while (*str && (*str != '<' && *str != '>'))
				str++;
			break ;
		}
		else if (!q.quote_flag && (*str == '<' || *str == '>'))
		{
			while (*str && (*str == '<' || *str == '>'))
				str++;
			break ;
		}
		else
			str++;
	}
	return (str - tmp);
}
int	check_redir_error(char *str)
{
	while (*str)
	{
		if (*str == '<' && *(str + 1) == '<')
		{
			str += 2;
			while (*str && *str == ' ')
				str++;
			if (*str == '<' || *str == '>')
				return (*str);
		}
		str++;
	}
	return (0);
}

char	**parse_by_redir(char *str)
{
	char	**arr;
	int		i;
	int		len;

	if (!check_redir_error(str))
		return (NULL);
	arr = malloc(sizeof(char *) * (count_redir_str(str) + 1));
	i = 0;
	ft_printf("count_redir: %d\n\n", count_redir_str(str));
	while (*str)
	{
		len = redir_str_len(str);
		arr[i] = malloc(sizeof(char) * (len + 1));
		ft_strlcpy(arr[i], str, len + 1);
		str += len;
		ft_printf("len: %d, %s\n", len, arr[i]);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
