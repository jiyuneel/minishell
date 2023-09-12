/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 05:08:06 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/13 05:23:17 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_exec/execute.h"

void	unlink_here_doc(t_cmd_info *cmd)
{
	t_redir	*node;

	while (cmd)
	{
		node = cmd->redir;
		while (node)
		{
			if (node->type == LEFT_2)
				unlink(node->filename);
			node = node->next;
		}
		cmd = cmd->next;
	}
}
