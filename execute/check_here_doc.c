/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 03:57:59 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/28 04:15:25 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	_get_here_doc_file(t_env_info *env, char *filename, char *limiter);

void	check_here_doc(t_shell_info *parse)
{
	t_cmd_info	*node;
	int			filenum;

	set_signal(HRD_CHILD, HRD_CHILD);
	filenum = 0;
	node = parse->cmd;
	while (node)
	{
		if (node->redir != NULL)
			change_hrd_to_infile(node->redir, parse->env, &filenum);
		node = node->next;
	}
	exit (EXIT_SUCCESS);
}

void	change_hrd_to_infile(t_redir *redir, t_env_info *env, int *filenum)
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
				exit (EXIT_FAILURE);
			redir->filename = remove_quotation(redir->filename, \
				ft_strlen(redir->filename));
			_get_here_doc_file(env, file, redir->filename);
			free (redir->filename);
			free (_num);
			redir->filename = file;
		}
		redir = redir->next;
	}
}

static void	_get_here_doc_file(t_env_info *env, char *filename, char *limiter)
{
	char	*line;
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_file_open("heredoc", TRUE);
	while (TRUE)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, limiter) == 0)
			break ;
		line = line_replace_env(env, line);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	if (line != NULL)
		free(line);
	close(fd);
}
