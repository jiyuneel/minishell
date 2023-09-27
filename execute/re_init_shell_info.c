/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_init_shell_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 03:07:19 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/28 04:15:59 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	_change_shell_info(t_shell_info *parse);
static void	_change_redir_filename(t_redir *redir, int *filenum);

int	re_init_shell_info(t_shell_info *parse)
{
	pid_t		pid;
	int			status;

	if (parse->heredoc_cnt == 0)
		return (_change_shell_info(parse));
	g_exit_code = 0;
	set_signal(IGNORE, IGNORE);
	pid = fork();
	if (pid < 0)
		exit (EXIT_FAILURE);
	else if (pid == 0)
		check_here_doc(parse);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == EXIT_FAILURE)
		g_exit_code = EXIT_FAILURE;
	set_signal(JIJI, JIJI);
	_change_shell_info(parse);
	if (g_exit_code == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	_change_shell_info(t_shell_info *parse)
{
	t_cmd_info	*node;
	int			idx;
	int			filenum;

	node = parse->cmd;
	filenum = 0;
	while (node)
	{
		_change_redir_filename(node->redir, &filenum);
		idx = 0;
		while (node->cmd_args[idx])
		{
			node->cmd_args[idx] = remove_quotation(node->cmd_args[idx], \
				ft_strlen(node->cmd_args[idx]));
			idx++;
		}
		node = node->next;
	}
	return (EXIT_SUCCESS);
}

static void	_change_redir_filename(t_redir *redir, int *filenum)
{
	char	*file;
	char	*_num;

	while (redir)
	{
		if (redir->type == LEFT_2)
		{
			free (redir->filename);
			_num = ft_itoa((*filenum)++);
			file = ft_strjoin(HERE_DOC, _num);
			if (file == NULL)
				exit (EXIT_FAILURE);
			free (_num);
			redir->filename = file;
		}
		else
			redir->filename = remove_quotation(redir->filename, \
				ft_strlen(redir->filename));
		redir = redir->next;
	}
}
