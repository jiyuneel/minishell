/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:51:59 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/11 00:40:58 by jiyunlee         ###   ########.fr       */
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
	while (1)
	{
		str = readline("jijishell$ ");
		if (!str)		// ctrl+D
			break ;
		shell_info.chunk_cnt = 0;
		shell_init(&shell_info, str);
		execute(&shell_info);
		add_history(str);
		free(str);
	}
	// free_env_info(shell_info.env);
	return (0);
}
