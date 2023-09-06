/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:40:35 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/06 22:03:40 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_exec/execute.h"

static void	_get_path_args(t_env_info *env, t_exec_info *exec);
static void	_get_envp(t_env_info *env, t_exec_info *exec);
static int	_get_envp_len(t_env_info *env);

t_exec_info	*init_exec_info(t_shell_info *parse)
{
	t_exec_info	*exec;

	exec = malloc(sizeof(t_exec_info));
	if (exec == NULL)
		return (NULL);		// 어떻게 처리할 지 고민(signal ?)
	ft_memset(parse, 0, sizeof(t_exec_info));
	_get_path_args(parse->env, exec);
	_get_envp(parse->env, exec);
	return (exec);;
}

static void	_get_path_args(t_env_info *env, t_exec_info *exec)
{
	t_env_info	*node;

	node = env;
	while (node)
	{
		if (ft_strcmp(node->key, "PATH") == 0)		// strncmp로 할건지 고민
			break ;
		node = node->next;
	}
	if (node == NULL || node->value == NULL)
	{
		exec->path_args = NULL;						// PATH 없는 경우 어떻게..?
		return ;
	}
	exec->path_args = ft_split(node->value, ':');
	if (exec->path_args == NULL)
		exit (EXIT_FAILURE);		// fail to split
}

static void	_get_envp(t_env_info *env, t_exec_info *exec)
{
	t_env_info	*node;
	char		*tmp;
	int			idx;

	if (env == NULL)
	{
		exec->envp = NULL;
		return ;
	}
	exec->envp = malloc(sizeof(char *) * (_get_envp_len(env) + 1));
	node = env;
	idx = 0;
	while (node)
	{
		tmp = ft_strjoin(node->key, "=");
		if (tmp == NULL)
			exit (EXIT_FAILURE);	// fail to strjoin
		exec->envp[idx] = ft_strjoin(tmp, node->value);
		free (tmp);
		if (exec->envp[idx] == NULL)
			exit (EXIT_FAILURE);	// fail to strjoin
		idx++;
		node = node->next;
	}
	exec->envp[idx] = NULL;
}

static int	_get_envp_len(t_env_info *env)
{
	t_env_info	*node;
	int			len;

	len = 0;
	node = env;
	while (node)
	{
		len++;
		node = node->next;
	}
	return (len);
}


// PATH 없애면 어떻게 해야 할 지 확실히 정하기
// 1. 원래 pipex에서는 infile outfile 다 만들어놓고 했으므로 문제가 없음
// 2. 실제 shell에서는 파일은 다 생성된 상태에서 하는데 이걸 어떻게 짤지 다시 고민할 것
