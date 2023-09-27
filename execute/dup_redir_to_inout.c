/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_redir_to_inout.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:58:22 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/28 04:21:34 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	_dup_redir_in(t_exec_info *exec, char *file, int child);
static int	_dup_redir_out(t_exec_info *exec, char *file, \
			t_token_type mode, int child);

int	dup_redir_to_inout(t_exec_info *exec, t_redir *redir, int child)
{
	t_redir	*node;
	int		status;

	if (redir == NULL)
		return (TRUE);
	status = TRUE;
	node = redir;
	while (node && status == TRUE)
	{
		if (node->type == LEFT_1 || node->type == LEFT_2)
			status = _dup_redir_in(exec, node->filename, child);
		else if (node->type == RIGHT_1 || node->type == RIGHT_2)
			status = _dup_redir_out(exec, node->filename, node->type, child);
		node = node->next;
	}
	return (status);
}

static int	_dup_redir_in(t_exec_info *exec, char *file, int child)
{
	exec->in_fd = open(file, O_RDONLY);
	if (exec->in_fd == -1 && child == TRUE)
		error_file_open(file, TRUE);
	else if (exec->in_fd == -1)
		return (error_file_open(file, FALSE));
	if (dup2(exec->in_fd, STDIN_FILENO) == -1)
		perror("dup2(stdin)");
	close(exec->in_fd);
	return (TRUE);
}

static int	_dup_redir_out(t_exec_info *exec, char *file, \
			t_token_type mode, int child)
{
	if (mode == RIGHT_1)
		exec->out_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		exec->out_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (exec->out_fd == -1 && child == TRUE)
		error_file_open(file, TRUE);
	else if (exec->out_fd == -1)
		return (error_file_open(file, FALSE));
	if (dup2(exec->out_fd, STDOUT_FILENO) == -1)
		perror("dup2(stdout)");
	close(exec->out_fd);
	return (TRUE);
}
