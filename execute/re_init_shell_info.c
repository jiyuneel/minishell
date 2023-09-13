/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_init_shell_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 03:07:19 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/13 17:02:33 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_exec/execute.h"

static void	_change_here_doc_to_infile(t_redir *redir, int *filenum);
static void	_get_here_doc_file(char *filename, char *limiter);

void	re_init_shell_info(t_shell_info *parse)
{
	t_cmd_info	*node;
	int			idx;
	int			len;
	int			filenum;

	// if (parse->here_doc_cnt >= 16)
	// 	error_message("too many here_doc\n");
	node = parse->cmd;
	filenum = 0;
	while (node)
	{
		if (node->redir != NULL)
			_change_here_doc_to_infile(node->redir, &filenum);
		idx = 0;
		while (node->cmd_args[idx])
		{
			len = ft_strlen(node->cmd_args[idx]);
			node->cmd_args[idx] = remove_quotation(node->cmd_args[idx], len);
			idx++;
		}
		node = node->next;
	}
}

static void	_change_here_doc_to_infile(t_redir *redir, int *filenum)
{
	char	*file;
	char	*_num;

	while (redir)
	{
		if (redir->type == LEFT_2)
		{
			_num = ft_itoa((*filenum)++);
			file = ft_strjoin(HERE_DOC, _num);
			if (file == NULL)
				exit (EXIT_FAILURE);		// 이전까지 생성한 file unlink해줘야 할수도..?(시그널인가)
			_get_here_doc_file(file, redir->filename);
			free (redir->filename);
			free (_num);
			redir->filename = file;
		}
		redir = redir->next;
	}
}

static void	_get_here_doc_file(char *filename, char *limiter)
{
	char	*line;
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
		// line = _check_env_in_line(line);
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
	free(limiter);
	close(fd);
}
