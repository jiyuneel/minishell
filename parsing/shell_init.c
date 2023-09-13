/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:24:08 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/13 00:33:15 by jiyunlee         ###   ########.fr       */
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

void	cmd_add_back(t_cmd_info **node, t_cmd_info *new)
{
	t_cmd_info	*tmp;

	if (!(*node))
		*node = new;
	else
	{
		tmp = *node;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	count_cmd(char *str)
{
	// redirection 제외하고 세기
	int		cnt;
	t_quote	q;

	cnt = 0;
	q.quote_flag = FALSE;
	while (*str)
	{
		check_quote(&q.quote_flag, &q.quote, *str);
		if (!q.quote_flag && *str != ' ')
		{
			cnt++;
			while (*str && *str != ' ')
				str++;
		}
		else
			str++;
	}
	return (cnt);
}

int	word_len(char *str)
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

void	cmd_init(t_shell_info *shell_info, t_cmd_info **cmd, char *str)
{
	t_cmd_info	*cmd_info;
	int			i;
	int			len;

	cmd_info = ft_calloc(1, sizeof(t_cmd_info));
	// if (!cmd_info)
	cmd_info->cmd_cnt = count_cmd(str);
	cmd_info->cmd_args = malloc(sizeof(char *) * (cmd_info->cmd_cnt + 1));
	// if (!cmd_info->cmd_args)
	cmd_info->next = NULL;
	i = 0;
	while (*str)
	{
		if (*str != ' ')
		{
			len = word_len(str);
			cmd_info->cmd_args[i] = malloc(sizeof(char) * (len + 1));
			// if (!cmd_info->cmd_args[i])
			ft_strlcpy(cmd_info->cmd_args[i++], str, len + 1);
			str += len;
		}
		else
			str++;
	}
	cmd_info->cmd_args[i] = NULL;
	redir_init(cmd_info);
	cmd_add_back(cmd, cmd_info);
	shell_info->chunk_cnt++;
}

void	shell_init(t_shell_info *shell_info, char *str)
{
	int		i;
	int		j;
	t_quote	q;
	char	*chunk;

	shell_info->cmd = NULL;
	q.quote_flag = FALSE;
	i = 0;
	j = 0;
	while (1)
	{
		check_quote(&q.quote_flag, &q.quote, str[j]);
		if (!q.quote_flag && (!str[j] || str[j] == '|'))
		{
			chunk = malloc(sizeof(char) * (j - i + 1));
			// if (!chunk)
			ft_strlcpy(chunk, &str[i], j - i + 1);
			cmd_init(shell_info, &shell_info->cmd, chunk);
			free(chunk);
			if (!str[j])
				break ;
			i = j + 1;
		}
		j++;
	}
}
