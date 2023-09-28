/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:24:08 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/29 01:01:36 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	shell_init(t_shell_info *shell_info, char *str)
{
	t_token	*token;

	token = NULL;
	if (handle_syntax_error(shell_info, token, str))
		return (EXIT_FAILURE);
	parse_by_pipe(&token, str);
	parse_by_redir(&token);
	parse_by_space(&token);
	delete_invalid_token(&token);
	shell_info->heredoc_cnt = 0;
	if (!token || handle_syntax_error(shell_info, token, str))
	{
		free_token(token);
		return (EXIT_FAILURE);
	}
	replace_env(shell_info->env, token);
	shell_info->chunk_cnt = 0;
	shell_info->cmd = NULL;
	cmd_init(&shell_info->cmd, token);
	cmd_args_init(shell_info, shell_info->cmd);
	free_token(token);
	return (EXIT_SUCCESS);
}
