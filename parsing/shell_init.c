/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:24:08 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/07 09:26:54 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_cmd(char *str, int start, int end)
{
	// redirection 제외하고 세기
	// quotation일 때 처리
	int	cnt;

	cnt = 0;
	while (start <= end)
	{
		if (str[start] != ' ')
		{
			cnt++;
			while (start <= end && str[start] != ' ')
				start++;
		}
		else
			start++;
	}
	return (cnt);
}

int	word_len(char *str, int start, int end)
{
	// quotation일 때 처리
	int	len;

	len = 0;
	while (start <= end && str[start] != ' ')
	{
		len++;
		start++;
	}
	return (len);
}

void	cmd_init(t_cmd_info **cmd, char *str, int start, int end)
{
	t_cmd_info	*cmd_info;
	int			i;

	cmd_info = malloc(sizeof(t_cmd_info));
	// if (!cmd_info)
	cmd_info->cmd_cnt = count_cmd(str, start, end);
	cmd_info->cmd_args = malloc(sizeof(char *) * (cmd_info->cmd_cnt + 1));
	// if (!cmd_info->cmd_args)
	cmd_info->next = NULL;
	i = 0;
	// while (start <= end)
	// {
		
	// 	start++;
	// }
	cmd_info->cmd_args[i] = NULL;
	*cmd = cmd_info;	// cmd_add_back
}

void	shell_init(t_shell_info *shell_info, char *str)
{
	int		i;
	int		j;
	// int		quote_flag;
	// char	quote;

	shell_info->cmd = NULL;
	// quote_flag = FALSE;
	i = 0;
	j = 0;
	while (1)
	{
		if (!str[j] || str[j] == '|')
		{
			cmd_init(&shell_info->cmd, str, i, j - 1);
			if (!str[j])
				break ;
			i = j + 1;
		}
		j++;
	}
	ft_printf("%d\n", shell_info->cmd->cmd_cnt);
}
