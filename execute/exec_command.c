/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:12:09 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/26 16:13:57 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	_if_abs_or_rel_path(t_exec_info *exec);
static char	*_get_command_path(t_exec_info *exec);

void	exec_command(t_exec_info *exec, int mode)
{
	char	*cmd_path;
	int		exit_code;

	if (exec->cmd_args[0] == NULL)
		exit (EXIT_SUCCESS);
	_if_abs_or_rel_path(exec);
	exit_code = 0;
	// "" 인 경우도 되는지 확인 -> mode로 왠만한 처리 될듯?
	if (mode == TRUE && is_builtin(exec, &exit_code) == TRUE)
		exit (exit_code);
	cmd_path = _get_command_path(exec);
	if (cmd_path == NULL)
		error_exit(exec->cmd_args[0], FALSE);
	execve(cmd_path, exec->cmd_args, exec->envp);
	error_exit(exec->cmd_args[0], EXIT_FAILURE);
}

static void	_if_abs_or_rel_path(t_exec_info *exec)
{
	if (exec->cmd_args[0][0] != '/' && exec->cmd_args[0][0] != '.')
		return ;
	if (exec->cmd_args[0][0] == '.')	// 예외처리--;
	{
		error_for_dot(exec->cmd_args[0], ft_strlen(exec->cmd_args[0]));
		if (exec->cmd_args[0][1] == '.' && exec->cmd_args[0][2] != '/')
			return ;
		if (exec->cmd_args[0][1] != '/' && exec->cmd_args[0][1] != '.')
			return ;
	}
	execve(exec->cmd_args[0], exec->cmd_args, exec->envp);
	error_no_auth(exec->cmd_args[0]);
}

static char	*_get_command_path(t_exec_info *exec)
{
	char	*cmd_path;
	char	*tmp;
	int		i;

	if (exec->cmd_args[0][0] == '\0')		// ""가 들어온 경우 예외 처리
		return (NULL);
	i = 0;
	if (exec->path_args == NULL)
		return (NULL);
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
