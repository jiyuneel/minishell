/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:12:09 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/28 02:32:38 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	_if_abs_or_rel_path(t_exec_info *exec, int child);
static char	*_get_command_path(t_exec_info *exec);

void	exec_command(t_exec_info *exec, int mode)
{
	char	*cmd_path;
	int		exit_code;

	if (exec->cmd_args[0] == NULL)
		exit (EXIT_SUCCESS);
	error_for_dot(exec->cmd_args[0], ft_strlen(exec->cmd_args[0]), FALSE);
	if (exec->path_args == NULL || exec->path_args[0] == NULL)
		error_no_auth(exec->cmd_args[0]);
	_if_abs_or_rel_path(exec, mode);
	exit_code = 0;
	if (mode == TRUE && is_builtin(exec, &exit_code, TRUE) == TRUE)
		exit (exit_code);
	cmd_path = _get_command_path(exec);
	if (cmd_path == NULL)
		error_exit(exec->cmd_args[0], FALSE);
	execve(cmd_path, exec->cmd_args, exec->envp);
	error_exit(exec->cmd_args[0], EXIT_FAILURE);
}

static void	_if_abs_or_rel_path(t_exec_info *exec, int child)
{
	if (exec->cmd_args[0][0] != '/' && exec->cmd_args[0][0] != '.')
		return ;
	if (exec->cmd_args[0][0] == '.')
	{
		error_for_dot(exec->cmd_args[0], ft_strlen(exec->cmd_args[0]), TRUE);
		if (exec->cmd_args[0][1] == '.' && exec->cmd_args[0][2] != '/')
			return ;
		if (exec->cmd_args[0][1] != '/' && exec->cmd_args[0][1] != '.')
			return ;
	}
	if (child == TRUE && ft_strcmp(exec->cmd_args[0], "./minishell") == 0)
	{
		ft_putstr_fd("The default interactive shell is not jijishell.\n", \
			STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	execve(exec->cmd_args[0], exec->cmd_args, exec->envp);
	error_no_auth(exec->cmd_args[0]);
}

static char	*_get_command_path(t_exec_info *exec)
{
	char	*cmd_path;
	char	*tmp;
	int		i;

	if (exec->cmd_args[0][0] == '\0')
		return (NULL);
	i = 0;
	while (exec->path_args[i])
	{
		tmp = ft_strjoin(exec->path_args[i], "/");
		if (tmp == NULL)
			exit (EXIT_FAILURE);
		cmd_path = ft_strjoin(tmp, exec->cmd_args[0]);
		free (tmp);
		if (cmd_path == NULL)
			exit (EXIT_FAILURE);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free (cmd_path);
		i++;
	}
	return (NULL);
}
