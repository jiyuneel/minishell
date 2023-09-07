/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:51:59 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/07 16:29:27 by jihykim2         ###   ########.fr       */
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
	/* env 출력 */
	// for (t_env_info *tmp = shell_info.env; tmp; tmp = tmp->next)
	// 	ft_printf("key: %s, value: %s\n", tmp->key, tmp->value);
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
	return (0);
}
