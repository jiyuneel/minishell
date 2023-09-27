/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:52:40 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/27 12:28:07 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*_get_home_path(t_env_info **env);
static void	_change_pwd(t_env_info **env, char *prev_path);

int	cd(t_exec_info *exec)
{
	char	*path;
	char	*prev_path;

	if (exec->cmd_args[1] == NULL || ft_strcmp(exec->cmd_args[1], "~") == 0)
		path = _get_home_path(exec->env);
	else
		path = exec->cmd_args[1];
	if (path == NULL)
	{
		error_message("cd", NULL, "HOME not set");
		return (EXIT_FAILURE);
	}
	prev_path = getcwd(NULL, 0);
	if (chdir(path) == EXIT_SUCCESS)
		_change_pwd(exec->env, prev_path);
	else
	{
		free (prev_path);
		ft_putstr_fd("jijishell: ", STDERR_FILENO);
		perror("cd");
		return (EXIT_FAILURE);
	}
	free (prev_path);
	return (EXIT_SUCCESS);
}

static char	*_get_home_path(t_env_info **env)
{
	t_env_info	*node;

	node = *env;
	while (node)
	{
		if (strcmp(node->key, "HOME") == 0)
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

static void	_change_pwd(t_env_info **env, char *prev_path)
{
	t_env_info	*node;

	node = *env;
	while (node)
	{
		if (strcmp(node->key, "PWD") == 0)
		{
			if (node->value != NULL)
				free (node->value);
			node->value = getcwd(NULL, 0);
		}
		else if (strcmp(node->key, "OLDPWD") == 0)
		{
			if (node->value != NULL)
				free (node->value);
			node->value = ft_strdup(prev_path);
		}
		node = node->next;
	}
}
