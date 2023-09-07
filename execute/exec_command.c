/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:12:09 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/07 15:56:24 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_exec/execute.h"

static char	*_check_command_path(t_exec_info *exec);

void	exec_command(t_exec_info *exec)
{
	char	*cmd_path;

	cmd_path = _check_command_path(exec);
	if (cmd_path == NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(exec->cmd_args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit (127);
	}
	if (execve(cmd_path, exec->cmd_args, exec->envp) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(exec->cmd_args[0]);
		free (cmd_path);
		exit (127);
	}
}

static char	*_check_command_path(t_exec_info *exec)
{
	char	*cmd_path;
	char	*tmp;
	int		i;

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
