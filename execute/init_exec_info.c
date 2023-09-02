/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:40:35 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/02 21:40:02 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_exec/execute.h"

t_exec_info	*init_exec_info(t_shell_info *parse, char **env)
{
	t_exec_info	*exec;

	exec = malloc(sizeof(t_exec_info));
	if (exec == NULL)
		return (NULL);		// 어떻게 처리할 지 고민
	ft_memset(parse, 0, sizeof(t_exec_info));
	exec->env = parse->env;
	_get_path_arr(parse->env, exec);

	return (exec);;
}

static void	_get_path_arr(t_env_info *env, t_exec_info *exec)
{
	t_env_info	*node;

	if (env == NULL)
		exit (EXIT_FAILURE);	// 어떻게 처리할 지 고민
	node = env;
	while (node)
	{
		if (ft_strncmp(node->key, "PATH", 5) == 0)
			break ;
		node = node->next;
	}
	if (node == NULL || node->value == NULL)
		exit (EXIT_FAILURE);		// PATH 없는 경우 어떻게..?
}

// PATH 없애면 어떻게 해야 할 지 확실히 정하기
// 1. 원래 pipex에서는 infile outfile 다 만들어놓고 했으므로 문제가 없음
// 2. 실제 shell에서는 파일은 다 생성된 상태에서 하는데 이걸 어떻게 짤지 다시 고민할 것













/*
static void	_get_path_arr(t_exec_info *p)	// pipex 방법
{
	char	*env_path;
	int		i;

	if (p->envp == NULL)
		exit (EXIT_FAILURE);
	i = 0;
	while (p->envp[i])
	{
		if (ft_strncmp(p->envp[i], "PATH=", 5) == 0)
		{
			env_path = p->envp[i] + 5;
			break ;
		}
		i++;
	}
	if (p->envp[i] == NULL || *env_path == 0)
		exit (EXIT_FAILURE);
	p->path = ft_split(env_path, ':');
	if (p->path == NULL)
		exit (EXIT_FAILURE);
}
*/
