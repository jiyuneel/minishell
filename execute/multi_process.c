/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:01:06 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/07 14:55:53 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_exec/execute.h"

void	parent_process(t_exec_info *exec)
{
	close (exec->pipe[P_WRITE]);
	if (dup2(exec->pipe[P_READ], STDIN_FILENO) == -1)
		perror("dup2(stdin)");
	close(exec->pipe[P_READ]);
}

void	child_process(t_exec_info *exec, t_cmd_info *node)
{
	close(exec->pipe[P_READ]);
	if (dup2(exec->pipe[P_WRITE], STDOUT_FILENO) == -1)
		perror("dup2(pipe_write)");
	close(exec->pipe[P_WRITE]);
	_dup_redir_to_inout(exec, node->redir);
	exec_command(exec);
}
