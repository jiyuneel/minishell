/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:01:06 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/28 03:31:35 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	_parent_process(t_exec_info *exec);
static void	_child_process(t_exec_info *exec, t_cmd_info *cmd, int end);

void	multi_process(t_exec_info *exec, t_cmd_info *cmd, int chunk_cnt)
{
	pid_t	pid;
	int		idx;

	idx = 1;
	set_signal(IGNORE, IGNORE);
	while (cmd)
	{
		exec->cmd_args = cmd->cmd_args;
		if (pipe(exec->pipe) == -1)
			error_exit("pipe", EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			error_exit("fork", EXIT_FAILURE);
		else if (pid == 0)
			_child_process(exec, cmd, chunk_cnt - idx);
		else
			_parent_process(exec);
		cmd = cmd->next;
		idx++;
	}
	wait_child(pid, chunk_cnt);
}

static void	_parent_process(t_exec_info *exec)
{
	close (exec->pipe[P_WRITE]);
	if (dup2(exec->pipe[P_READ], STDIN_FILENO) == -1)
		perror("dup2(stdin)");
	close(exec->pipe[P_READ]);
}

static void	_child_process(t_exec_info *exec, t_cmd_info *cmd, int end)
{
	set_signal(DEFAULT, DEFAULT);
	close(exec->pipe[P_READ]);
	if (end != 0 && dup2(exec->pipe[P_WRITE], STDOUT_FILENO) == -1)
		perror("dup2(pipe_write)");
	close(exec->pipe[P_WRITE]);
	dup_redir_to_inout(exec, cmd->redir, TRUE);
	exec_command(exec, TRUE);
}
