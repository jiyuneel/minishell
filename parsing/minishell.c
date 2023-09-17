/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:51:59 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/18 01:09:52 by jiyunlee         ###   ########.fr       */
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
		if (!str[0])	// enter
			continue ;
		if (!shell_init(&shell_info, str))
			execute(&shell_info);
		// print_shell_info(&shell_info);
		add_history(str);
		free(str);
	}
	free_env_info(shell_info.env);
	return (0);
}

/* shell_info 출력 */
void	print_shell_info(t_shell_info *shell_info)
{
	ft_printf("chunk_cnt: %d\n\n", shell_info->chunk_cnt);
	for (t_cmd_info *tmp = shell_info->cmd; tmp; tmp = tmp->next)
	{
		ft_printf("[----- cmd -----]\n");
		ft_printf("cmd_cnt: %d\n", tmp->cmd_cnt);
		// for (t_str *s = tmp->str; s; s = s->next) {
		// 	ft_printf("%d %s\n", s->type, s->command);
		// }
		for (int i = 0; tmp->cmd_args[i]; i++)
			ft_printf("%s\n", tmp->cmd_args[i]);
		ft_printf("[---- redir ----]\n");
		for (t_redir *r = tmp->redir; r; r = r->next) {
			ft_printf("%d %s\n", r->type, r->filename);
		}
		ft_printf("\n-----------------\n\n");
	}
}
