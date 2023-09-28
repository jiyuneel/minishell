/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:04:46 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/29 01:01:11 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_env(char *str, t_env_info **env_var);
void	get_env_value(t_env_info *env, t_env_info *tmpenv);
void	expand_env(t_token *token, t_env_info *env_var);

void	replace_env(t_env_info *env, t_token *token)
{
	t_token_type	prev_type;
	t_env_info		*env_var;

	prev_type = 0;
	while (token)
	{
		if (!(IRD <= prev_type && prev_type <= ARD)
			&& token->type == STR)
		{
			env_var = NULL;
			find_env(token->value, &env_var);
			get_env_value(env, env_var);
			expand_env(token, env_var);
			free_env_info(env_var);
		}
		prev_type = token->type;
		token = token->next;
	}
}

t_env_info	*tmpenv_new_node(char *key, int idx)
{
	t_env_info	*node;

	node = ft_calloc(1, sizeof(t_env_info));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = NULL;
	node->idx = idx;
	node->next = NULL;
	return (node);
}

void	find_env(char *str, t_env_info **env_var)
{
	t_quote		q;
	int			i;
	int			j;

	q.quote_flag = FALSE;
	i = 0;
	while (str[i])
	{
		check_quote(&q, str[i]);
		if ((!q.quote_flag || (q.quote_flag && q.quote == '\"')) \
			&& str[i] == '$')
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

void	get_env_value(t_env_info *env, t_env_info *env_var)
{
	t_env_info	*tmp;
	char		*exit_code;

	while (env_var)
	{
		if (!ft_strcmp(env_var->key, "?"))
		{
			exit_code = ft_itoa(g_exit_code);
			env_var->value = ft_strdup(exit_code);
			free(exit_code);
		}
		tmp = env;
		while (tmp)
		{
			if (!ft_strcmp(env_var->key, tmp->key))
			{
				env_var->value = ft_strdup(tmp->value);
				break ;
			}
			tmp = tmp->next;
		}
		env_var = env_var->next;
	}
}

void	expand_env(t_token *token, t_env_info *env_var)
{
	char	*env_front;
	char	*env_back;
	char	*str;
	int		idx_back;

	while (env_var)
	{
		env_front = ft_strndup(token->value, env_var->idx);
		idx_back = env_var->idx + ft_strlen(env_var->key) + 1;
		env_back = ft_strdup(token->value + idx_back);
		free(token->value);
		if (env_var->value)
			str = ft_strjoin(env_front, env_var->value);
		else
			str = ft_strjoin(env_front, "");
		token->value = ft_strjoin(str, env_back);
		free(env_front);
		free(env_back);
		free(str);
		env_var = env_var->next;
	}
}
