/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 01:54:31 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/25 02:57:35 by jiyunlee         ###   ########.fr       */
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
	t_env_info	*tmp;

	tmp = env;
	sort_env(tmp);
	while (tmp)
	{
		if (tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("declare -x %s", tmp->key);
		tmp = tmp->next;
	}
}

void	print_export_error(char *identifier)
{
	printf("jijishell: export: `%s\': not a valid identifier\n", identifier);
	g_exit_code = 1;
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

// void	export(t_shell_info *exec)
void	export(t_exec_info *exec)
{
	int	i;

	if (!exec->cmd_args[1])
		print_export(exec->env);
	i = 1;
	while (exec->cmd_args[i])
	{
		if (!is_valid_export_identifier(exec->cmd_args[i]))
		{
			print_export_error(exec->cmd_args[i]);
			i++;
			continue ;
		}
		// export_env
		i++;
	}
	g_exit_code = 0;
}
