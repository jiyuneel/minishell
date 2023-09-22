/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:04:46 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/22 20:06:25 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env_info	*tmpenv_new_node(char *key, int idx);
t_env_info	*find_env(char *str);
void		get_env_value(t_env_info *env, t_env_info *tmpenv);

void	replace_env(t_env_info *env, t_token *token)
{
	t_env_info		*tmpenv;
	t_env_info		*tmp;
	t_token_type	prev_type;
	char			*env_front;
	char			*env_back;
	char			*str;
	int				idx_back;

	prev_type = 0;
	while (token)
	{
		if (!(LEFT_1 <= prev_type && prev_type <= RIGHT_2) && token->type == STR)
		{
			tmpenv = find_env(token->value);
			get_env_value(env, tmpenv);
			// print_env(tmpenv);
			tmp = tmpenv;
			while (tmp)
			{
				env_front = malloc(sizeof(char) * (tmp->idx + 1));
				ft_strlcpy(env_front, token->value, tmp->idx + 1);
				idx_back = tmp->idx + ft_strlen(tmp->key) + 1;
				env_back = ft_strdup(token->value + idx_back);
				free(token->value);
				if (tmp->value)
					str = ft_strjoin(env_front, tmp->value);
				else
					str = ft_strjoin(env_front, "");
				token->value = ft_strjoin(str, env_back);
				free(env_front);
				free(env_back);
				free(str);
				tmp = tmp->next;
			}

			free_env_info(tmpenv);
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

t_env_info	*find_env(char *str)
{
	t_env_info	*env;
	t_quote		q;
	int			i;
	int			j;
	char		*key;

	env = NULL;
	q.quote_flag = FALSE;
	i = 0;
	while (str[i])
	{
		check_quote(&q.quote_flag, &q.quote, str[i]);
		if ((!q.quote_flag || (q.quote_flag && q.quote == '\"')) && str[i] == '$')
		{
			j = i + 1;
			if (str[j] == '?')
				j++;
			else if (ft_isdigit(str[j]))
				j++;
			else
				while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
					j++;
			if (i + 1 != j)
			{
				key = malloc(sizeof(char) * (j - i));
				ft_strlcpy(key, &str[i + 1], j - i);
				env_add_front(&env, tmpenv_new_node(key, i));
			}
			i = j;
		}
		else
			i++;
	}
	return (env);
}

void	get_env_value(t_env_info *env, t_env_info *tmpenv)
{
	t_env_info	*tmp;

	while (tmpenv)
	{
		if (!ft_strcmp(tmpenv->key, "?"))
			tmpenv->value = ft_strdup(ft_itoa(g_exit_code));
		tmp = env;
		while (tmp)
		{
			if (!ft_strcmp(tmpenv->key, tmp->key))
			{
				tmpenv->value = ft_strdup(tmp->value);
				break ;
			}
			tmp = tmp->next;
		}
		tmpenv = tmpenv->next;
	}
}



/* env 출력 */
void	print_env(t_env_info *env)
{
	for (t_env_info *tmp = env; tmp; tmp = tmp->next)
	{
		printf("[------- env -------]\n");
		printf("%d %s %s\n", tmp->idx, tmp->key, tmp->value);
	}
}
