/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:28:46 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/25 17:02:53 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(t_exec_info *exec, int *exit_code)
{
	int	flag;

	flag = FALSE;
	// if (ft_strcmp(exec->cmd_args[0], "echo") == 0 && ++flag)
	// 	*exit_code = echo(exec);
	if (ft_strcmp(exec->cmd_args[0], "cd") == 0 && ++flag)		// parent
		*exit_code = cd(exec);
	else if (ft_strcmp(exec->cmd_args[0], "pwd") == 0 && ++flag)	// parent
		*exit_code = pwd(exec);
	else if (ft_strcmp(exec->cmd_args[0], "export") == 0 && ++flag)	// parent
		*exit_code = export(exec);
	else if (ft_strcmp(exec->cmd_args[0], "unset") == 0 && ++flag)	// parent
		*exit_code = unset(exec);
	else if (ft_strcmp(exec->cmd_args[0], "env") == 0 && ++flag)
		*exit_code = env(exec);
	else if (ft_strcmp(exec->cmd_args[0], "exit") == 0 && ++flag)	// parent
		*exit_code = exit_with_args(exec);		// exit(g_exit_code)인지 다시 확인하기...
	if (flag == FALSE)
		return (FALSE);
	return (TRUE);
}
