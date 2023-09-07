/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:58:22 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/07 15:13:39 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_exec/execute.h"

static void	_dup_redir_out(t_exec_info *exec, char *file, t_token_type mode);
static void	_dup_redir_in(t_exec_info *exec, char *file, t_token_type mode);
static int	_get_here_doc_file_fd(t_exec_info *exec, char *limiter);

void	dup_redir_to_inout(t_exec_info *exec, t_redir *redir)
{
	t_redir	*node;

	if (redir == NULL)
		return ;
	node = redir;
	while (node)
	{
		if (node->type == RIGHT_1 || node->type == RIGHT_2)
			_dup_redir_out(exec, node->filename, node->type);
		else if (node->type == LEFT_1 || node->type == LEFT_2)
			_dup_redir_in(exec, node->filename, node->type);
		node = node->next;
	}
}

static void	_dup_redir_out(t_exec_info *exec, char *file, t_token_type mode)
{
	if (mode == RIGHT_1)
		exec->out_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		exec->out_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (exec->out_fd == -1)
	{
		perror(file);
		exit (EXIT_FAILURE);
	}
	if (dup2(exec->out_fd, STDOUT_FILENO) == -1)
		perror("dup2(stdout)");
	close(exec->out_fd);
}

static void	_dup_redir_in(t_exec_info *exec, char *file, t_token_type mode)
{
	if (mode == LEFT_1)
		exec->in_fd = open(file, O_RDONLY);
	else
		exec->in_fd = _get_here_doc_file_fd(exec, file);
	if (exec->in_fd == -1)
	{
		perror(file);
		exit (EXIT_FAILURE);
	}
	if (dup2(exec->in_fd, STDIN_FILENO) == -1)
		perror("dup2(stdin)");
	close(exec->in_fd);
}

static int	_get_here_doc_file_fd(t_exec_info *exec, char *limiter)
{
	char	*line;
	int		fd;

	exec->here_doc = TRUE;
	fd = open(HERE_DOC, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror("open(here_doc)");
	limiter = ft_strjoin(limiter, "\n");
	if (limiter == NULL)
		exit (EXIT_FAILURE);
	while (TRUE)
	{
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			exit (EXIT_FAILURE);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
	close(fd);
	return (open(HERE_DOC, O_RDONLY));
}
