/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:44:58 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/07 16:29:27 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes_exec/execute.h"

/* [실행부 함수 시작] */
int	execute(t_shell_info *parse)
{
	t_exec_info		*exec;
	t_cmd_info		*node;		// next == NULL 까지 fork 실행
	pid_t			pid;		// kill을 사용할까...?
	int				status;

	// if (parse->cmd->next == NULL && parse->cmd->cmd_cnt == 1)
	// 	single_command(parse);		// 부모에서 실행되는 경우 -> flag 만들까(?)
	exec = init_exec_info(parse);
	node = parse->cmd;
	while (node)
	{
		exec->cmd_args = node->cmd_args;	// split_command(node, exec);
		if (pipe(exec->pipe) == -1)
			exit (EXIT_FAILURE);			// pipe error
		pid = fork();
		if (pid == -1)
			exit (EXIT_FAILURE);			// fork error
		else if (pid == 0)
			child_process(exec, node);
		else
			parent_process(exec);
		// free_cmd_args(exec->cmd_args);
		node = node->next;
	}
	while (parse->chunk_cnt--)
		wait(&status);
	// free_cmd_info();
	// free_exec_info();
	return (EXIT_SUCCESS);
}

// void	split_command(t_cmd_info *node, t_exec_info *exec)
// {

// }


/* [execute.c]
 * node마다 fork를 할 것이므로 execve를 위한 인자 setting
 * 		-> path_args: env의 PATH를 split한 결과
 * 		-> char **envp 전체가 필요한데 이는 어떻게 처리..?(env에 대한 연산 시 달라지기 때문)
 * fork를 할 때마다
 * 	(실행 전)
 * 		-> cmd들 모두 split하기(word 배열.. 처리)
 * 	(자식)
 * 		-> dup2로 redirection에 대한 출입구 정리
 * 		-> 사용하지 않는 파이프 닫아주기
 * 	(부모)
 * 		-> 이전 파이프와 연결하고 동시에 사용하지 않는 파이프 닫기
 * 	(실행 후)
 * 		-> split했던 cmd_args(exec) 모두 free 후 node(parse) 이동
 *
 * [아직 하지 않은 부분]
 * 1. built-in functions: 구현 -> single_command() 구현
 * 2. 부모에서만 실행 될 인자들 따로 처리
 * 3. signal 처리 및 exit_code 처리
 * 4. here_doc에서 환경변수가 입력된 경우 해당 값으로 치환하여 저장해야 함
*/
