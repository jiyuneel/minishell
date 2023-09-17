/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:24:08 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/18 01:08:06 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	cmd_add_back(t_cmd_info **node, t_cmd_info *new);
void	cmd_init(t_cmd_info **cmd, t_token *token);
void	cmd_args_init(t_shell_info *shell_info, t_cmd_info *cmd);

int	shell_init(t_shell_info *shell_info, char *str)
{
	t_token	*token;

	token = NULL;
	if (handle_syntax_error(token, str))
		return (EXIT_FAILURE);
	parse_by_pipe(&token, str);
	parse_by_redir(&token);
	parse_by_space(&token);
	delete_invalid_token(&token);
	// print_token(token);
	if (handle_syntax_error(token, str))
	{
		free_token(token);
		return (EXIT_FAILURE);
	}
	shell_info->chunk_cnt = 0;
	shell_info->cmd = NULL;
	cmd_init(&shell_info->cmd, token);
	cmd_args_init(shell_info, shell_info->cmd);
	free_token(token);
	return (EXIT_SUCCESS);
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

void	cmd_init(t_cmd_info **cmd, t_token *token)
{
	t_cmd_info		*cmd_info;
	t_token_type	type;

	cmd_info = ft_calloc(1, sizeof(t_cmd_info));
	while (token)
	{
		if (token->type == STR)
		{
			cmd_info->cmd_cnt++;
			str_add_back(&cmd_info->str, str_new_node(ft_strdup(token->value)));
		}
		else if (LEFT_1 <= token->type && token->type <= RIGHT_2)
		{
			type = token->type;
			token = token->next;
			redir_add_back(&cmd_info->redir, redir_new_node(type, ft_strdup(token->value)));
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

/* token 출력 */
void	print_token(t_token *token)
{
	for (t_token *tmp = token; tmp; tmp = tmp->next)
	{
		// if (!tmp->valid)
		// 	continue ;
		printf("[------- token -------]\n");
		if (tmp->type == STR)
			printf("STR ");
		else if (tmp->type == PIPE)
			printf("PIPE ");
		else if (tmp->type == LEFT_1)
			printf("LEFT_1 ");
		else if (tmp->type == LEFT_2)
			printf("LEFT_2 ");
		else if (tmp->type == RIGHT_1)
			printf("RIGHT_1 ");
		else if (tmp->type == RIGHT_2)
			printf("RIGHT_2 ");
		if (tmp->valid)
			printf("valid\n");
		else
			printf("invalid\n");
		printf("\'%s\'\n\n", tmp->value);
	}
}
