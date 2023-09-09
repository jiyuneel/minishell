/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:24:08 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/09 12:50:27 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	// quotation일 때 처리
	int		cnt;
	int		quote_flag;
	char	quote;

	cnt = 0;
	quote_flag = FALSE;
	while (*str)
	{
		if (!quote_flag && (*str == '\'' || *str == '\"'))
		{
			quote_flag = TRUE;
			quote = *str;
		}
		else if (quote_flag && *str == quote)
			quote_flag = FALSE;
		if (!quote_flag && *str != ' ')
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
	int		quote_flag;
	char	quote;

	len = 0;
	quote_flag = FALSE;
	while (*str)
	{
		if (!quote_flag && (*str == '\'' || *str == '\"'))
		{
			quote_flag = TRUE;
			quote = *str;
		}
		else if (quote_flag && *str == quote)
			quote_flag = FALSE;
		if (!quote_flag && *str == ' ')
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

	cmd_info = malloc(sizeof(t_cmd_info));
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
	cmd_add_back(cmd, cmd_info);
	shell_info->chunk_cnt++;
}

void	shell_init(t_shell_info *shell_info, char *str)
{
	int		i;
	int		j;
	int		quote_flag;
	char	quote;
	char	*chunk;

	shell_info->cmd = NULL;
	quote_flag = FALSE;
	i = 0;
	j = 0;
	while (1)
	{
		if (!quote_flag && (str[j] == '\'' || str[j] == '\"'))
		{
			quote_flag = TRUE;
			quote = str[j];
		}
		else if (quote_flag && str[j] == quote)
			quote_flag = FALSE;
		if (!quote_flag && (!str[j] || str[j] == '|'))
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
	/* shell_info 출력 */
	// for (t_cmd_info *tmp = shell_info->cmd; tmp; tmp = tmp->next)
	// {
	// 	ft_printf("%d\n", tmp->cmd_cnt);
	// 	for (int i = 0; tmp->cmd_args[i]; i++)
	// 		ft_printf("%s\n", tmp->cmd_args[i]);
	// 	ft_printf("||\n");
	// }
	// ft_printf("%d\n", shell_info->chunk_cnt);
}
