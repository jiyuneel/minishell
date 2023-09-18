/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:08:44 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/16 14:47:33 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

void	error_file_open(char *filename)
{
	ft_putstr_fd("jijishell: ", STDERR_FILENO);
	perror(filename);
	exit (EXIT_FAILURE);
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