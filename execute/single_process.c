/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:34:05 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/26 16:12:45 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	_exec_in_child(t_exec_info *exec);

int	single_process(t_exec_info *exec, t_cmd_info *cmd)
{
	int	exit_code;

	exec->cmd_args = cmd->cmd_args;
	exit_code = 0;
	set_signal(DEFAULT, DEFAULT);
	dup_redir_to_inout(exec, cmd->redir);
	if (is_builtin(exec, &exit_code) == TRUE)
		g_exit_code = exit_code;
	else
		_exec_in_child(exec);
	return (TRUE);
}

static void	_exec_in_child(t_exec_info *exec)
{
	pid_t	pid;

	set_signal(IGNORE, IGNORE);
	pid = fork();
	if (pid == -1)
		error_exit("fork", EXIT_FAILURE);
	else if (pid == 0)
	{
		set_signal(DEFAULT, DEFAULT);
		exec_command(exec, FALSE);
	}
	wait_child(pid, 1);
}
