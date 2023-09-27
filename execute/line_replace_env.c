/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_replace_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 00:59:37 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/27 09:54:52 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	line_find_env(char *str, t_env_info **env_var);
char	*line_expand_env(char *str, t_env_info *env_var);

char	*line_replace_env(t_env_info *env, char *str)
{
	t_env_info	*env_var;
	char		*line;

	env_var = NULL;
	line_find_env(str, &env_var);
	get_env_value(env, env_var);
	line = line_expand_env(str, env_var);
	free_env_info(env_var);
	return (line);
}

void	line_find_env(char *str, t_env_info **env_var)
{
	int			i;
	int			j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = i + 1;
			if (str[j] == '?' || ft_isdigit(str[j]))
				j++;
			else
				while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
					j++;
			if (i + 1 != j)
				env_add_front(env_var, \
					tmpenv_new_node(ft_strndup(&str[i + 1], j - i - 1), i));
			i = j - 1;
		}
		i++;
	}
}

char	*line_expand_env(char *str, t_env_info *env_var)
{
	char	*env_front;
	char	*env_back;
	char	*tmp;
	int		idx_back;

	while (env_var)
	{
		env_front = ft_strndup(str, env_var->idx);
		idx_back = env_var->idx + ft_strlen(env_var->key) + 1;
		env_back = ft_strdup(str + idx_back);
		free(str);
		if (env_var->value)
			tmp = ft_strjoin(env_front, env_var->value);
		else
			tmp = ft_strjoin(env_front, "");
		str = ft_strjoin(tmp, env_back);
		free(env_front);
		free(env_back);
		free(tmp);
		env_var = env_var->next;
	}
	return (str);
}
