/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 01:54:31 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/29 00:16:24 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sort_env(t_env_info *env)
{
	t_env_info	*tmp1;
	t_env_info	*tmp2;
	char		*tmp_key;
	char		*tmp_value;

	tmp1 = env;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp1->key, tmp2->key) > 0)
			{
				tmp_key = tmp1->key;
				tmp1->key = tmp2->key;
				tmp2->key = tmp_key;
				tmp_value = tmp1->value;
				tmp1->value = tmp2->value;
				tmp2->value = tmp_value;
			}
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
}

void	print_export(t_env_info *env)
{
	t_env_info	*sorted_env;
	t_env_info	*tmp;

	sorted_env = NULL;
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			env_add_back(&sorted_env, env_new_node(ft_strdup(tmp->key), ft_strdup(tmp->value)));
		else
			env_add_back(&sorted_env, env_new_node(ft_strdup(tmp->key), NULL));
		tmp = tmp->next;
	}
	sort_env(sorted_env);
	tmp = sorted_env;
	while (tmp)
	{
		if (tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
	free_env_info(sorted_env);
}

int	is_valid_export_identifier(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (FALSE);
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

void	export_env(t_env_info **env, char *str)
{
	t_env_info	*tmp;
	char		*key;
	char		*value;
	int			key_len;

	key_len = 0;
	while (str[key_len] && str[key_len] != '=')
		key_len++;
	key = ft_strndup(str, key_len);
	if (str[key_len] == '=')
		value = ft_strdup(str + key_len + 1);
	else
		value = NULL;
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->key))
		{
			free(tmp->value);
			tmp->value = value;
			return ;
		}
		else
			tmp = tmp->next;
	}
	env_add_back(env, env_new_node(key, value));
}

int	export(t_exec_info *exec)
{
	int	error_flag;
	int	i;

	error_flag = FALSE;
	if (!exec->cmd_args[1])
		print_export(*exec->env);
	else
	{
		i = 1;
		while (exec->cmd_args[i])
		{
			if (!is_valid_export_identifier(exec->cmd_args[i]))
			{
				error_flag = TRUE;
				printf("jijishell: export: `%s\': not a valid identifier\n", \
					exec->cmd_args[i]);
			}
			else
				export_env(exec->env, exec->cmd_args[i]);
			i++;
		}
	}
	return (error_flag);
}
