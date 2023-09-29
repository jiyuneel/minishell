/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_with_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:52:40 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/29 15:17:43 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	_arg_to_int(char *arg, int *is_invalid);
static int	_invalid_len(unsigned long long res, char c, int len);

int	exit_with_args(t_exec_info *exec, int child)
{
	int	exit_code;
	int	is_invalid;

	if (child == TRUE)
		g_exit_code = 0;
	else
		printf("exit\n");
	if (exec->cmd_args[1] == NULL)
		set_origin_exit(exec->origin_term, g_exit_code, child);
	is_invalid = FALSE;
	exit_code = _arg_to_int(exec->cmd_args[1], &is_invalid);
	if (is_invalid == TRUE)
		error_message("exit", exec->cmd_args[1], "numeric argument required");
	if (is_invalid == TRUE || exec->cmd_args[2] == NULL)
		set_origin_exit(exec->origin_term, exit_code, child);
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
		if ((ft_isdigit(*arg) == FALSE || _invalid_len(res, *arg, len)) \
			&& ++(*is_invalid))
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

static int	_invalid_len(unsigned long long res, char c, int len)
{
	unsigned long long	calculated_value;

	if (len < 20)
		return (FALSE);
	calculated_value = res * 10 + (c - '0');
	if (calculated_value < res)
		return (TRUE);
	return (FALSE);
}
