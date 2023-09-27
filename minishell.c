/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:51:59 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/27 12:51:15 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	g_exit_code;

static void	_init_term(t_shell_info *shell_info, int argc, char **argv);
static void	_set_origin_term(t_shell_info *shell_info);

void leaks(void)
{
	system("leaks -q $PPID");
}

int	main(int argc, char **argv, char **envp)
{
	t_shell_info	shell_info;
	char			*str;

	// atexit(leaks);
	_init_term(&shell_info, argc, argv);
	env_init(&shell_info.env, envp);
	while (TRUE)
	{
		str = readline("\033[37;1mjijishell$ "); // \033[94m
		if (!str)		// ctrl+D
			break ;
		if (!str[0])	// enter
		{
			free(str);
			continue ;
		}
		if (!shell_init(&shell_info, str))
			execute(&shell_info);
		// print_shell_info(&shell_info);
		add_history(str);
		free(str);
	}
	_set_origin_term(&shell_info);
	return (g_exit_code);		// exit?? ^^
}

static void	_init_term(t_shell_info *shell_info, int argc, char **argv)
{
	struct termios	term;

	(void) argv;
	if (argc != 1)
		exit (EXIT_FAILURE);
	g_exit_code = 0;
	tcgetattr(STDIN_FILENO, &shell_info->origin_term);	// 현재 shell 상태 저장
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);					// 해당 flag로 shell의 출력 제어
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal(JIJI, JIJI);
}

static void	_set_origin_term(t_shell_info *shell_info)
{
	free_env_info(shell_info->env);
	printf("\x1b[1A\033[11Cexit\n", STDOUT_FILENO);
	set_signal(DEFAULT, DEFAULT);		// 꼭 있어야 할까..?
	tcsetattr(STDIN_FILENO, TCSANOW, &shell_info->origin_term);	// 모든 것이 끝났으므로 다시 원상 복귀
}





/* shell_info 출력 */
void	print_shell_info(t_shell_info *shell_info)
{
	printf("chunk_cnt: %d\n\n", shell_info->chunk_cnt);
	for (t_cmd_info *tmp = shell_info->cmd; tmp; tmp = tmp->next)
	{
		printf("[----- cmd -----]\n");
		printf("cmd_cnt: %d\n", tmp->cmd_cnt);
		// for (t_str *s = tmp->str; s; s = s->next) {
		// 	printf("%d %s\n", s->type, s->command);
		// }
		for (int i = 0; tmp->cmd_args[i]; i++)
			printf("%s\n", tmp->cmd_args[i]);
		printf("[---- redir ----]\n");
		for (t_redir *r = tmp->redir; r; r = r->next) {
			printf("%d %s\n", r->type, r->filename);
		}
		printf("\n-----------------\n\n");
	}
}
