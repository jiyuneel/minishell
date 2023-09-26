/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_origin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 04:43:08 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/27 04:45:27 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_origin_exit(struct termios origin, int exit_code, int child)
{
	if (child == TRUE)
		exit (exit_code);
	tcsetattr(STDIN_FILENO, TCSANOW, &origin);
	set_signal(DEFAULT, DEFAULT);
	exit (exit_code);
}
