/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:26:20 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/25 02:55:12 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_unset_error(char *identifier)
{
	printf("jijishell: unset: `%s\': not a valid identifier\n", identifier);
	g_exit_code = 1;
}

int	is_valid_unset_identifier(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (FALSE);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

void	delete_env(t_env_info **env, t_env_info **node)
{
	t_env_info	*prev;

	if (*node == *env)
	{
		*env = (*env)->next;
		free((*node)->key);
		free((*node)->value);
		free(*node);
		*node = *env;
	}
	else
	{
		prev = *env;
		while (prev->next != *node)
			prev = prev->next;
		free((*node)->key);
		free((*node)->value);
		free(*node);
		*node = prev->next;
	}
}

void	unset_env(t_env_info **env, char *str)
{
	t_env_info	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->key))
		{
			delete_env(env, &tmp);
			break ;
		}
		else
			tmp = tmp->next;
	}
}

void	unset(t_exec_info *exec)
{
	int	i;

	i = 1;
	while (exec->cmd_args[i])
	{
		if (!is_valid_unset_identifier(exec->cmd_args[i]))
		{
			print_unset_error(exec->cmd_args[i]);
			i++;
			continue ;
		}
		unset_env(&exec->env, exec->cmd_args[i]);
		i++;
	}
	g_exit_code = 0;
}
