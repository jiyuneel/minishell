/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:40:35 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/28 02:52:25 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	_get_path_args(t_exec_info *exec);
static void	_get_envp(t_exec_info *exec);
static int	_get_envp_len(t_env_info *env);

t_exec_info	*init_exec_info(t_shell_info *parse)
{
	t_exec_info	*exec;

	exec = malloc(sizeof(t_exec_info));
	if (exec == NULL)
		exit (EXIT_FAILURE);
	ft_memset(exec, 0, sizeof(t_exec_info));
	exec->env = &(parse->env);
	_get_path_args(exec);
	_get_envp(exec);
	exec->origin_term = parse->origin_term;
	return (exec);
}

static void	_get_path_args(t_exec_info *exec)
{
	t_env_info	*node;

	node = *exec->env;
	while (node)
	{
		if (ft_strcmp(node->key, "PATH") == 0)
			break ;
		node = node->next;
	}
	if (node == NULL || node->value == NULL)
		return ;
	exec->path_args = ft_split(node->value, ':');
	if (exec->path_args == NULL)
		exit (EXIT_FAILURE);
}

static void	_get_envp(t_exec_info *exec)
{
	t_env_info	*node;
	char		*tmp;
	int			idx;

	node = *exec->env;
	if (node == NULL)
		return ;
	exec->envp = ft_calloc(_get_envp_len(node) + 1, sizeof(char *));
	idx = 0;
	while (node)
	{
		if (node->value != NULL)
		{
			tmp = ft_strjoin(node->key, "=");
			if (tmp == NULL)
				exit (EXIT_FAILURE);
			exec->envp[idx] = ft_strjoin(tmp, node->value);
			free (tmp);
			if (exec->envp[idx] == NULL)
				exit (EXIT_FAILURE);
			idx++;
		}
		node = node->next;
	}
}

static int	_get_envp_len(t_env_info *env)
{
	int	len;

	len = 0;
	while (env)
	{
		if (env->value != NULL)
			len++;
		env = env->next;
	}
	return (len);
}
