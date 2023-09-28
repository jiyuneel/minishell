/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:51:59 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/29 01:12:59 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	g_exit_code;

static void	_init_term(t_shell_info *shell_info, int argc, char **argv);
static void	_set_origin_term(t_shell_info *shell_info);

int	main(int argc, char **argv, char **envp)
{
	t_shell_info	shell_info;
	char			*str;

	_init_term(&shell_info, argc, argv);
	env_init(&shell_info.env, envp);
	while (TRUE)
	{
		str = readline("\033[37;1mjijishell$ ");
		if (!str)
			break ;
		if (!str[0])
		{
			free(str);
			continue ;
		}
		if (!shell_init(&shell_info, str))
			execute(&shell_info);
		add_history(str);
		free(str);
	}
	_set_origin_term(&shell_info);
	return (g_exit_code);
}

static void	_init_term(t_shell_info *shell_info, int argc, char **argv)
{
	struct termios	term;

	(void) argv;
	if (argc != 1)
		exit (EXIT_FAILURE);
	g_exit_code = 0;
	tcgetattr(STDIN_FILENO, &shell_info->origin_term);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal(JIJI, JIJI);
}

static void	_set_origin_term(t_shell_info *shell_info)
{
	free_env_info(shell_info->env);
	printf("\x1b[1A\033[11Cexit\n", STDOUT_FILENO);
	set_signal(DEFAULT, DEFAULT);
	tcsetattr(STDIN_FILENO, TCSANOW, &shell_info->origin_term);
}
