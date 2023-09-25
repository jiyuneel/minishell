/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:58:11 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/25 14:58:12 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		key = ft_strndup(*envp, key_len);
		value = ft_strndup(*envp + key_len + 1, value_len);
		env_add_back(env, env_new_node(key, value));
		envp++;
	}
}
