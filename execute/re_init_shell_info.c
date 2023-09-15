/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_init_shell_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 03:07:19 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/15 22:16:00 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_exec/execute.h"

static void	_check_here_doc(t_shell_info *parse);
static int	_change_shell_info(t_shell_info *parse);
static void	_change_here_doc_to_infile(t_redir *redir, int *filenum, int mode);
static void	_get_here_doc_file(char *filename, char *limiter);

/* error_code 반환 */
int	re_init_shell_info(t_shell_info *parse)
{
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid < 0)
		exit (EXIT_FAILURE);
	else if (pid == 0)
		_check_here_doc(parse);
	waitpid(pid, &status, 0);		// status 값으로 해당 에러코드 반환하고 종료하기
	// if (WIFEXITED(status) == 0)
	// 	return (_change_shell_info(parse));		// here_doc이 끝나고 나면 진행
	// return (258);	// syntax error
	_change_shell_info(parse);
	return (EXIT_SUCCESS);
}

/* child process: 위 함수에 합칠까? */
static void	_check_here_doc(t_shell_info *parse)
{
	t_cmd_info	*node;
	int			filenum;

	// if (parse->here_doc_cnt >= 16)
	// 	error_message("too many here_doc\n");  >> 파싱에서 에초에 쉘이 종료되어야 함!!
	filenum = 0;
	node = parse->cmd;
	while (node)
	{
		_change_here_doc_to_infile(node->redir, &filenum, TRUE);
		node = node->next;
	}
	// signal에 대한 처리 진행 -> 이때 파일 삭제할 수 있으면 모두 삭제 진행
	exit (EXIT_SUCCESS);
}

/* parent process: rename filename(hrd) & remove quotation*/
static int	_change_shell_info(t_shell_info *parse)	// parent process
{
	t_cmd_info	*node;
	int			idx;
	int			len;
	int			filenum;

	node = parse->cmd;
	filenum = 0;
	while (node)
	{
		_change_here_doc_to_infile(node->redir, &filenum, FALSE);
		idx = 0;
		while (node->cmd_args[idx])
		{
			len = ft_strlen(node->cmd_args[idx]);
			node->cmd_args[idx] = remove_quotation(node->cmd_args[idx], len);
			idx++;
		}
		node = node->next;
	}
	return (EXIT_SUCCESS);
}

static void	_change_here_doc_to_infile(t_redir *redir, int *filenum, int mode)
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
			if (mode == TRUE)
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
		error_file_open("heredoc");
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
