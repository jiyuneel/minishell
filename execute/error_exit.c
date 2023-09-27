/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:08:44 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/28 03:44:19 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_exit(char *cmd, int sys_errno)
{
	if (sys_errno == FALSE)
	{
		error_message(cmd, NULL, "command not found");
		exit (127);
	}
	else
	{
		ft_putstr_fd("jijishell: ", STDERR_FILENO);
		perror(cmd);
		exit (sys_errno);
	}
}

int	error_file_open(char *filename, int exit_mode)
{
	ft_putstr_fd("jijishell: ", STDERR_FILENO);
	perror(filename);
	if (exit_mode == TRUE)
		exit (EXIT_FAILURE);
	return (FALSE);
}

void	error_for_dot(char *cmd, int len, int mode)
{
	if (len == 1 && cmd[0] == '.')
	{
		ft_putstr_fd("jijishell: ", STDERR_FILENO);
		ft_putstr_fd(".: filename argument required\n", STDERR_FILENO);
		ft_putstr_fd(".: usage: . filename [arguments]\n", STDERR_FILENO);
		exit (2);
	}
	else if (mode == TRUE && len == 2 && cmd[1] == '.')
		error_exit(cmd, FALSE);
}

void	error_no_auth(char *cmd)
{
	int	is_dir;

	is_dir = FALSE;
	if (access(cmd, X_OK) == 0 && ++is_dir)
		error_message(cmd, NULL, "is a directory");
	else
	{
		ft_putstr_fd("jijishell: ", STDERR_FILENO);
		perror(cmd);
	}
	if (is_dir == TRUE || errno == 13)
		exit (126);
	exit (127);
}
