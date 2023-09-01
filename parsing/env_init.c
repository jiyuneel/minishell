/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:58:11 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/01 19:15:14 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

void	env_init(t_env_info **env_info, char **envp)
{
	char	*key;
	char	*value;
	// char	*str;
	int		i;
	int		j;

	i = 0;
	*env_info = NULL;
	while (envp[i])
	{
		// str = *envp;
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		key = malloc(sizeof(char) * j + 1);
		value = malloc(sizeof(char) * (ft_strlen(envp[i]) - j));
		// if (!key) if (!value)
		ft_strlcpy(key, envp[i], j + 1);
		ft_strlcpy(value, envp[i] + j + 1, ft_strlen(envp[i]) - j);
		env_add_back(env_info, env_new_node(key, value));
		i++;
	}
}
