/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:24:08 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/07 16:29:27 by jihykim2         ###   ########.fr       */
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

void	cmd_init(t_shell_info *shell_info, t_cmd_info **cmd, char *str, int start, int end)
{
	t_cmd_info	*cmd_info;
	int			i;
	int			len;

	cmd_info = malloc(sizeof(t_cmd_info));
	// if (!cmd_info)
	cmd_info->cmd_cnt = count_cmd(str, start, end);
	cmd_info->cmd_args = malloc(sizeof(char *) * (cmd_info->cmd_cnt + 1));
	// if (!cmd_info->cmd_args)
	cmd_info->next = NULL;
	i = 0;
	while (start <= end)
	{
		if (str[start] != ' ')
		{
			len = word_len(str, start, end);
			cmd_info->cmd_args[i] = malloc(sizeof(char) * (len + 1));
			// if (!cmd_info->cmd_args[i])
			ft_strlcpy(cmd_info->cmd_args[i++], &str[start], len + 1);
			start += len;
		}
		else
			start++;
	}
	cmd_info->cmd_args[i] = NULL;
	// *cmd = cmd_info;	// cmd_add_back
	cmd_add_back(cmd, cmd_info);
	shell_info->chunk_cnt++;
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
			cmd_init(shell_info, &shell_info->cmd, str, i, j - 1);
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
