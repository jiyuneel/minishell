/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 05:08:06 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/29 00:26:33 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unlink_here_doc(t_cmd_info *cmd)
{
	t_redir	*node;

	while (cmd)
	{
		node = cmd->redir;
		while (node)
		{
			if (node->type == HRD)
				unlink(node->filename);
			node = node->next;
		}
		cmd = cmd->next;
	}
}
