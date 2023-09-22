/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:12:09 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/22 15:22:20 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*_check_command_path(t_exec_info *exec);

void	exec_command(t_exec_info *exec)
{
	char	*cmd_path;

	if (exec->cmd_args[0] == NULL)
		exit (EXIT_SUCCESS);
	cmd_path = _check_command_path(exec);
	if (cmd_path == NULL)
		error_exit(exec->cmd_args[0], FALSE);
	if (execve(cmd_path, exec->cmd_args, exec->envp) != 0)
		error_exit("execve", EXIT_FAILURE);
}

static char	*_check_command_path(t_exec_info *exec)
{
	char	*cmd_path;
	char	*tmp;
	int		i;

	if (exec->cmd_args[0][0] == '\0')		// ""가 들어온 경우 예외 처리
		return (NULL);
	if (access(exec->cmd_args[0], X_OK) == 0)
		return (ft_strdup(exec->cmd_args[0]));
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
