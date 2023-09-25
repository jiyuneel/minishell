/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:46:29 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/25 16:48:41 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_child(pid_t last_pid, int chunk_cnt)
{
	pid_t	child;
	int		status;
	int		idx;
	int		print_flag;

	idx = 0;
	print_flag = 0;
	while (idx < chunk_cnt)
	{
		child = waitpid(-1, &status, 0);
		if (WIFSIGNALED(status) == TRUE && ++print_flag)
		{
			if (WTERMSIG(status) == SIGINT && print_flag == TRUE)
				ft_putstr_fd("^C\n", STDERR_FILENO);
			else if (WTERMSIG(status) == SIGQUIT && print_flag == TRUE)
				ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
			if (child == last_pid)
				g_exit_code = 128 + WTERMSIG(status);
		}
		else if (child == last_pid)
			g_exit_code = WEXITSTATUS(status);
		idx++;
	}
}
