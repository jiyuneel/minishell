/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:58:22 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/15 21:59:15 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_exec/execute.h"

static void	_dup_redir_in(t_exec_info *exec, char *file);
static void	_dup_redir_out(t_exec_info *exec, char *file, t_token_type mode);

void	dup_redir_to_inout(t_exec_info *exec, t_redir *redir)
{
	t_redir	*node;

	if (redir == NULL)
		return ;
	node = redir;
	while (node)
	{
		if (node->type == LEFT_1 || node->type == LEFT_2)
			_dup_redir_in(exec, node->filename);
		else if (node->type == RIGHT_1 || node->type == RIGHT_2)
			_dup_redir_out(exec, node->filename, node->type);
		node = node->next;
	}
}

static void	_dup_redir_in(t_exec_info *exec, char *file)
{
	exec->in_fd = open(file, O_RDONLY);
	if (exec->in_fd == -1)
		error_file_open(file);
	if (dup2(exec->in_fd, STDIN_FILENO) == -1)
		perror("dup2(stdin)");
	close(exec->in_fd);
}

static void	_dup_redir_out(t_exec_info *exec, char *file, t_token_type mode)
{
	if (mode == RIGHT_1)
		exec->out_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		exec->out_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (exec->out_fd == -1)
		error_file_open(file);
	if (dup2(exec->out_fd, STDOUT_FILENO) == -1)
		perror("dup2(stdout)");
	close(exec->out_fd);
}
