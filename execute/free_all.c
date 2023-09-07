/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:21:17 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/08 02:35:28 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_exec/execute.h"

void	free_cmd_info(t_cmd_info *cmd)
{
	t_cmd_info	*tmp;

	if (cmd == NULL)
		return ;
	while (cmd)
	{
		tmp = cmd->next;
		free_arr(cmd->cmd_args);
		free_redir(cmd->redir);
		free (cmd);
		cmd = tmp;
	}
}

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	if (redir == NULL)
		return ;
	while (redir)
	{
		tmp = redir->next;
		free (redir->filename);
		free (redir);
		redir = tmp;
	}
}

void	free_env_info(t_env_info *env)
{
	t_env_info	*tmp;

	if (env == NULL)
		return ;
	while (env)
	{
		tmp = env->next;
		free (env->key);
		free (env->value);
		free (env);
		env = tmp;
	}
}

void	free_exec_info(t_exec_info *exec)
{
	if (exec == NULL)
		return ;
	// free_arr(exec->cmd_args);	// 아직 파싱 전이라,,
	free_arr(exec->path_args);
	free_arr(exec->envp);
}

void	free_arr(char **arr)
{
	int	idx;

	if (arr == NULL)
		return ;
	idx = 0;
	while (arr[idx])
		free (arr[idx++]);
	free (arr);
}
