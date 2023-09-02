/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:44:58 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/02 21:41:44 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes_exec/execute.h"

int	execute(t_shell_info *parse, char **env);

int	main(int ac, char **av, char **env)
{
	t_shell_info	*parse;

	parse = malloc(sizeof(t_shell_info));
	if (parse == NULL)
		return (EXIT_FAILURE);
	parse->pipe_cnt = 1;
	parse->env = init_env(env);
	parse->cmd_node = init_cmd_node();

	return (execute(parse, env));
}

/* [실행부 함수 시작] */
int	execute(t_shell_info *parse, char **env)	// env 없애기
{
	t_exec_info		*exec;
	pid_t			pid;		// kill을 사용할까...?
	t_cmd_info		*node;		// next == NULL 까지 fork 실행

	if (parse->pipe_cnt == 0 && parse->cmd_node->cmd_cnt == 1)
		single_command(parse);		// 부모에서 실행되는 경우 -> flag 만들까(?)

	exec = init_exec_info(parse, env);

	node = parse->cmd_node;
	while (node)
	{
		re_init_exec_info(node, exec);

		// fork
		// muilti-processing
		free_cmd_args(exec->cmd_args);		// 위치 다시 선정
		node = node->next;
	}
}

