/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:44:58 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/25 01:20:30 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	_free_n_set_origin(t_shell_info *parse, t_exec_info *exec, \
	int stdin_origin, int stdout_origin);

void	execute(t_shell_info *parse)
{
	t_exec_info		*exec;
	int				stdin_origin;
	int				stdout_origin;

	if (re_init_shell_info(parse) == EXIT_FAILURE)
	{
		_free_n_set_origin(parse, exec, stdin_origin, stdout_origin);
		return ;
	}
	set_signal(IGNORE, IGNORE);
	exec = init_exec_info(parse);
	stdin_origin = dup(STDIN_FILENO);
	stdout_origin = dup(STDOUT_FILENO);
	// if (parse->cmd->next == NULL && parse->cmd->cmd_cnt == 1)
	// 	single_command(parse);		// 부모에서 실행되는 경우 -> flag 만들까(?)
	// else
	multi_process(exec, parse->cmd, parse->chunk_cnt);
	_free_n_set_origin(parse, exec, stdin_origin, stdout_origin);
}

static void	_free_n_set_origin(t_shell_info *parse, t_exec_info *exec, \
	int stdin_origin, int stdout_origin)
{
	free_cmd_info(parse->cmd);
	parse->cmd = NULL;
	if (exec != NULL)
	{
		free_exec_info(exec);
		if (dup2(stdin_origin, STDIN_FILENO) == -1)
			exit (EXIT_FAILURE);
		if (dup2(stdout_origin, STDOUT_FILENO) == -1)
			exit (EXIT_FAILURE);
		close(stdin_origin);
		close(stdout_origin);
	}
	set_signal(JIJI, JIJI);
}
