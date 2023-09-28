/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:40:28 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/29 00:36:44 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_add_back(t_cmd_info **node, t_cmd_info *new);

void	cmd_init(t_cmd_info **cmd, t_token *token)
{
	t_cmd_info		*cmd_info;

	cmd_info = ft_calloc(1, sizeof(t_cmd_info));
	while (token)
	{
		if (token->type == STR)
		{
			cmd_info->cmd_cnt++;
			str_add_back(&cmd_info->str, str_new_node(ft_strdup(token->value)));
		}
		else if (IRD <= token->type && token->type <= ARD)
		{
			redir_add_back(&cmd_info->redir, \
				redir_new_node(token->type, ft_strdup(token->next->value)));
			token = token->next;
		}
		else if (token->type == PIPE)
		{
			cmd_add_back(cmd, cmd_info);
			cmd_info = ft_calloc(1, sizeof(t_cmd_info));
		}
		token = token->next;
	}
	cmd_add_back(cmd, cmd_info);
}

void	cmd_args_init(t_shell_info *shell_info, t_cmd_info *cmd)
{
	int		i;
	t_str	*tmp;

	while (cmd)
	{
		shell_info->chunk_cnt++;
		cmd->cmd_args = ft_calloc(cmd->cmd_cnt + 1, sizeof(char *));
		i = 0;
		tmp = cmd->str;
		while (tmp)
		{
			cmd->cmd_args[i++] = ft_strdup(tmp->command);
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
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
