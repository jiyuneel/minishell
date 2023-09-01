/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:51:59 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/01 18:18:29 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int main(int argc, char **argv, char **envp)
{
	// t_shell_info	shell_info;
	t_env_info		*env_info;

	(void) argv;
	if (argc != 1)
		return (1);		// error
	env_init(&env_info, envp);
	for (t_env_info *tmp = env_info; tmp; tmp = tmp->next)
		ft_printf("key: %s, value: %s\n", tmp->key, tmp->value);
	return 0;
}
