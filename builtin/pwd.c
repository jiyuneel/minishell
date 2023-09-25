/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:52:40 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/25 21:54:37 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd(t_exec_info *exec)
{
	char	*current_path;

	(void)exec;
	current_path = getcwd(NULL, 0);
	if (current_path == NULL)
		error_exit("getcwd", EXIT_FAILURE);
	printf("%s\n", current_path);
	free (current_path);
	return (EXIT_SUCCESS);
}
