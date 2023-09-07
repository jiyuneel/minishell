/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:51:59 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/06 21:04:02 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell_info	shell_info;
	char			*str;

	(void) argv;
	if (argc != 1)
		return (1);		// error
	env_init(&shell_info.env, envp);
	for (t_env_info *tmp = shell_info.env; tmp; tmp = tmp->next)
		ft_printf("key: %s, value: %s\n", tmp->key, tmp->value);
	while (1)
	{
		str = readline("jijishell$ ");
		if (!str)		// ctrl+D
			break ;
		shell_init(&shell_info, str);
		// ft_printf("str = %s\n", str);
		add_history(str);
		free(str);
	}
	return (0);
}
