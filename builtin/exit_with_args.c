/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_with_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:52:40 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/26 23:28:11 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	_arg_to_int(char *arg, int *is_invalid);

int	exit_with_args(t_exec_info *exec, int child)
{
	int	exit_code;
	int	is_invalid;

	if (child == TRUE)
		g_exit_code = 0;
	else
		printf("exit\n");
	if (exec->cmd_args[1] == NULL)
		exit (g_exit_code);
	is_invalid = FALSE;
	exit_code = _arg_to_int(exec->cmd_args[1], &is_invalid);
	if (is_invalid == TRUE)
		error_message("exit", exec->cmd_args[1], "numeric argument required");
	if (is_invalid == TRUE || exec->cmd_args[2] == NULL)
		exit (exit_code);
	error_message("exit", NULL, "too many arguments");
	return (EXIT_FAILURE);
}

static int	_arg_to_int(char *arg, int *is_invalid)
{
	unsigned long long	res;
	int					sign;
	int					len;

	res = 0;
	len = 0;
	sign = 1;
	if ((*arg == '+' || *arg == '-') && *arg++ == '-')
		sign *= -1;
	while (*arg && *is_invalid == FALSE)
	{
		len++;
		if ((isdigit(*arg) == FALSE || len > 19) && ++(*is_invalid))
			return (255);
		res = res * 10 + (*arg++ - '0');
		if (sign == 1 && res > 9223372036854775807)
			++(*is_invalid);
		else if (res > 0 && sign == -1 && res - 1 > 9223372036854775807)
			++(*is_invalid);
	}
	if (*is_invalid == TRUE)
		return (255);
	return (res * sign);
}
