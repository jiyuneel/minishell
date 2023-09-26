/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:26:05 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/27 01:53:51 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	_find_print_index(char **args, int *option);
static int	_is_option(char *s);
static void	_print_args(char **print_args, int option);

int	echo(t_exec_info *exec)
{
	int	option;
	int	print_idx;

	option = FALSE;
	print_idx = _find_print_index(exec->cmd_args, &option);
	if (print_idx == 0)
		printf("\n");
	else
		_print_args(exec->cmd_args + print_idx, option);
	return (EXIT_SUCCESS);
}

static int	_find_print_index(char **args, int *option)
{
	int	idx;

	idx = 1;
	if (args[idx] == NULL)
		return (0);
	while (args[idx])
	{
		if (_is_option(args[idx]) == TRUE)
			*option = TRUE;
		else
			break ;
		idx++;
	}
	return (idx);
}

static int	_is_option(char *s)
{
	if (*s != '-')
		return (FALSE);
	s++;
	while (*s)
		if (*s++ != 'n')
			return (FALSE);
	return (TRUE);
}

static void	_print_args(char **print_args, int option)
{
	if (*print_args == NULL)
		return ;
	while (*print_args)
	{
		printf("%s", *print_args);
		print_args++;
		if (*print_args != NULL)
			printf(" ");
	}
	if (option == FALSE)
		printf("\n");
}
