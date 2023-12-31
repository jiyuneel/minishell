/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:28:46 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/27 05:29:20 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(t_exec_info *exec, int *exit_code, int child)
{
	int	flag;

	flag = FALSE;
	if (exec->cmd_args[0] == NULL)
		return (FALSE);
	if (ft_strcmp(exec->cmd_args[0], "echo") == 0 && ++flag)
		*exit_code = echo(exec);
	else if (ft_strcmp(exec->cmd_args[0], "cd") == 0 && ++flag)
		*exit_code = cd(exec);
	else if (ft_strcmp(exec->cmd_args[0], "pwd") == 0 && ++flag)
		*exit_code = pwd(exec);
	else if (ft_strcmp(exec->cmd_args[0], "export") == 0 && ++flag)
		*exit_code = export(exec);
	else if (ft_strcmp(exec->cmd_args[0], "unset") == 0 && ++flag)
		*exit_code = unset(exec);
	else if (ft_strcmp(exec->cmd_args[0], "env") == 0 && ++flag)
		*exit_code = env(exec);
	else if (ft_strcmp(exec->cmd_args[0], "exit") == 0 && ++flag)
		*exit_code = exit_with_args(exec, child);
	if (flag == FALSE)
		return (FALSE);
	return (TRUE);
}
