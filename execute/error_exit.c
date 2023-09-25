/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:08:44 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/25 00:45:19 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_file_open(char *filename)
{
	ft_putstr_fd("jijishell: ", STDERR_FILENO);
	perror(filename);
	exit (EXIT_FAILURE);
}

void	error_for_dot(char *cmd, int len)
{
	if (len == 1)
	{
		ft_putstr_fd("jijishell: ", STDERR_FILENO);
		ft_putstr_fd(".: filename argument required\n", STDERR_FILENO);
		ft_putstr_fd(".: usage: . filename [arguments]\n", STDERR_FILENO);
		exit (2);
	}
	else if (len == 2 && cmd[1] == '.')
		error_exit(cmd, FALSE);
}

void	error_no_auth(char *cmd)
{
	int	is_dir;

	is_dir = FALSE;
	ft_putstr_fd("jijishell: ", STDERR_FILENO);
	if (access(cmd, X_OK) == 0 && ++is_dir)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
	}
	else
		perror(cmd);
	if (is_dir == TRUE || errno == 13)
		exit (126);
	exit (127);
}

void	error_exit(char *cmd, int sys_errno)
{
	if (sys_errno == FALSE)
	{
		ft_putstr_fd("jijishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit (127);
	}
	else
	{
		ft_putstr_fd("jijishell: ", STDERR_FILENO);
		perror(cmd);
		exit (sys_errno);
	}
}
