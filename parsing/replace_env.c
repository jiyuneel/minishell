/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:04:46 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/18 21:28:56 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tmp_env	*tmp_env_new_node(int idx, char *key);
void		tmp_env_add_back(t_tmp_env **node, t_tmp_env *new);

t_tmp_env	*find_env(char *str)
{
	t_tmp_env	*env;
	t_quote		q;
	int			i;
	int			j;

	env = NULL;
	q.quote_flag = FALSE;
	i = 0;
	while (str[i])
	{
		check_quote(&q.quote_flag, &q.quote, str[i]);
		if (!q.quote_flag || (q.quote_flag && q.quote == '\"'))
		{
			if (str[i] == '$')
			{
				j = i + 1;
				while (str[j] && (ft_isalpha(str[j]) || str[j] == '_'))
					j++;
				if (i != j)
				{
				}
			}
		}
		i++;
	}
}

void	replace_env(t_token *token)
{
	while (token)
	{
		if (token->type == STR)
		{
		}
		token = token->next;
	}
}

t_tmp_env	*tmp_env_new_node(int idx, char *key)
{
	t_tmp_env	*node;

	node = malloc(sizeof(t_tmp_env));
	if (!node)
		return (NULL);
	node->idx = idx;
	node->key = key;
	node->next = NULL;
	return (node);
}

void	tmp_env_add_back(t_tmp_env **node, t_tmp_env *new)
{
	t_tmp_env	*tmp;

	if (!(*node))
		*node = new;
	else
	{
		tmp = *node;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
