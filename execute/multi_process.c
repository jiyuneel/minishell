/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:01:06 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/08 04:55:25 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_exec/execute.h"

static void	_parent_process(t_exec_info *exec, int end);
static void	_child_process(t_exec_info *exec, t_cmd_info *node, int end);

void	multi_process(t_exec_info *exec, t_cmd_info *cmd, int chunk_cnt)
{
	pid_t	pid;
	int		idx;

	idx = 1;
	while (cmd)
	{
		exec->cmd_args = cmd->cmd_args;	// split_command(node, exec);
		if (pipe(exec->pipe) == -1)
			exit (EXIT_FAILURE);			// pipe error
		pid = fork();
		if (pid == -1)
			exit (EXIT_FAILURE);			// fork error
		else if (pid == 0)
			_child_process(exec, cmd, chunk_cnt - idx);
		else
			_parent_process(exec, chunk_cnt - idx);
		// free_arr(exec->cmd_args);
		cmd = cmd->next;
		idx++;
	}
}

static void	_parent_process(t_exec_info *exec, int end)
{
	close (exec->pipe[P_WRITE]);
	if (end != 0 && dup2(exec->pipe[P_READ], STDIN_FILENO) == -1)
		perror("dup2(stdin)");
	close(exec->pipe[P_READ]);
}

static void	_child_process(t_exec_info *exec, t_cmd_info *node, int end)
{
	close(exec->pipe[P_READ]);
	if (end != 0 && dup2(exec->pipe[P_WRITE], STDOUT_FILENO) == -1)
		perror("dup2(pipe_write)");
	close(exec->pipe[P_WRITE]);
	dup_redir_to_inout(exec, node->redir);
	exec_command(exec);
}
