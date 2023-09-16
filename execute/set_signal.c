/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 00:40:14 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/16 14:49:04 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

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
	if (sig_quit == IGNORE)
		signal(SIGQUIT, SIG_IGN);
	if (sig_quit == JIJI)
		signal(SIGQUIT, _jiji_handler);
	if (sig_quit == HRD_CHILD)
		signal(SIGQUIT, _hrd_handler);
}

static void	_jiji_handler(int sig_no)
{
	if (sig_no == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig_no == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	_hrd_handler(int sig_no)
{
	(void)sig_no;
}
