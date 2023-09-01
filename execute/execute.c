/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:44:58 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/01 00:28:28 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes_exec/execute.h"

int	main(int ac, char **av, char **env)
{
	t_shell_info	*exe;

	exe = malloc(sizeof(t_shell_info));
	if (exe == NULL)
		return (EXIT_FAILURE);

	exe->pipe_cnt = 1;
	exe->env = init_env(env);
	exe->cmd_node = init_cmd_node();

	return (execute_cmd(exe));
}

int	execute_cmd(t_shell_info *exe)		// 실행부 함수 시작
{
	if (exe->pipe_cnt == 0 && exe->cmd_node->cmd_cnt == 1)
		single_command(exe);
	multi_command(exe);
}
