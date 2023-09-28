/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:26:20 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/29 00:54:26 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_valid_unset_identifier(char *str);
void	unset_env(t_env_info **env, char *str);

int	unset(t_exec_info *exec)
{
	int	error_flag;
	int	i;

	error_flag = FALSE;
	i = 1;
	while (exec->cmd_args[i])
	{
		if (!is_valid_unset_identifier(exec->cmd_args[i]))
		{
			error_flag = TRUE;
			printf("jijishell: unset: `%s\': not a valid identifier\n", \
				exec->cmd_args[i]);
		}
		else
			unset_env(exec->env, exec->cmd_args[i]);
		i++;
	}
	return (error_flag);
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
		prev->next = (*node)->next;
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
