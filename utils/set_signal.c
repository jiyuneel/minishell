/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 00:40:14 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/23 02:37:56 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	_jiji_handler(int sig_no);
static void	_hrd_handler(int sig_no);

void	set_signal(int sig_int, int sig_quit)
{
	if (sig_int == DEFAULT)
		signal(SIGINT, SIG_DFL);
	if (sig_int == IGNORE)
		signal(SIGINT, SIG_IGN);
	if (sig_int == JIJI)
		signal(SIGINT, _jiji_handler);
	if (sig_int == HRD_CHILD)
		signal(SIGINT, _hrd_handler);
	if (sig_quit == DEFAULT)
		signal(SIGQUIT, SIG_DFL);
	if (sig_quit == IGNORE || sig_quit == JIJI || sig_quit == HRD_CHILD)
		signal(SIGQUIT, SIG_IGN);
}

static void	_jiji_handler(int sig_no)
{
	(void) sig_no;
	g_exit_code = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	_hrd_handler(int sig_no)
{
	(void) sig_no;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	exit (EXIT_FAILURE);
}
