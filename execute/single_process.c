/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:34:05 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/25 16:56:27 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	_check_exec_in_parent(t_exec_info *exec, int *exit_code);
static void	_exec_in_child(t_exec_info *exec);

int	single_process(t_exec_info *exec, t_cmd_info *cmd)
{
	int	exit_code;

	exec->cmd_args = cmd->cmd_args;
	exit_code = 0;
	dup_redir_to_inout(exec, cmd->redir);
	if (_check_exec_in_parent(exec, &exit_code) == TRUE)
		g_exit_code = exit_code;
	else
		_exec_in_child(exec);
	return (TRUE);
}

static int	_check_exec_in_parent(t_exec_info *exec, int *exit_code)
{
	int	flag;

	flag = 0;
	if (ft_strcmp(exec->cmd_args[0], "cd") == 0 && ++flag)			// parent
		*exit_code = cd(exec);
	else if (ft_strcmp(exec->cmd_args[0], "pwd") == 0 && ++flag)	// parent
		*exit_code = pwd(exec);
	else if (ft_strcmp(exec->cmd_args[0], "export") == 0 && ++flag)	// parent
		*exit_code = export(exec);
	else if (ft_strcmp(exec->cmd_args[0], "unset") == 0 && ++flag)	// parent
		*exit_code = unset(exec);
	else if (ft_strcmp(exec->cmd_args[0], "exit") == 0 && ++flag)	// parent
		*exit_code = exit_with_args(exec);
	if (flag == FALSE)
		return (FALSE);
	return (TRUE);
}

static void	_exec_in_child(t_exec_info *exec)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit("fork", EXIT_FAILURE);
	else if (pid == 0)
		exec_command(exec);
	wait_child(pid, 1);
}
