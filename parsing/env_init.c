/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:58:11 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/11 00:34:57 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_env_info	*env_new_node(char *key, char *value);
void		env_add_back(t_env_info **node, t_env_info *new);

void	env_init(t_env_info **env, char **envp)
{
	char	*key;
	char	*value;
	int		key_len;
	int		value_len;

	*env = NULL;
	while (*envp)
	{
		key_len = 0;
		while ((*envp)[key_len] && (*envp)[key_len] != '=')
			key_len++;
		value_len = ft_strlen(*envp) - key_len - 1;
		key = malloc(sizeof(char) * key_len + 1);
		value = malloc(sizeof(char) * value_len + 1);
		// if (!key) if (!value)
		ft_strlcpy(key, *envp, key_len + 1);
		ft_strlcpy(value, *envp + key_len + 1, value_len + 1);
		env_add_back(env, env_new_node(key, value));
		envp++;
	}
}

t_env_info	*env_new_node(char *key, char *value)
{
	t_env_info	*node;

	node = malloc(sizeof(t_env_info));
	if (!node)
		return (NULL);
	node->key = key;
    node->value = value;
	node->next = NULL;
	return (node);
}

void	env_add_back(t_env_info **node, t_env_info *new)
{
	t_env_info	*tmp;

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
