/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 01:00:07 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/12 23:55:04 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_redir_info	*redir_new_node(t_token_type type, char *filename)
{
	t_redir_info	*node;

	node = malloc(sizeof(t_redir_info));
	if (!node)
		return (NULL);
	node->type = type;
    node->filename = filename;
	node->next = NULL;
	return (node);
}

void	redir_add_back(t_redir_info **node, t_redir_info *new)
{
	t_redir_info	*tmp;

	if (!(*node))
		*node = new;
	else
	{
		tmp = *node;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	redir_init(t_cmd_info *cmd_info)
{
	int				i;
	t_token_type	type;
	char			*filename;

	i = 0;
	while (cmd_info->cmd_args[i])
	{
		if (cmd_info->cmd_args[i][0] == '<' && cmd_info->cmd_args[i][1] != '<')
		{
			type = LEFT_1;
			if (!cmd_info->cmd_args[i][1])
			{
				filename = ft_strdup(cmd_info->cmd_args[i + 1]);
			}
			// else
		}
		else if (cmd_info->cmd_args[i][0] == '<' && cmd_info->cmd_args[i][1] == '<')
		{
			type = LEFT_2;
		}
		else if (cmd_info->cmd_args[i][0] == '>' && cmd_info->cmd_args[i][1] != '>')
		{
			type = RIGHT_1;
		}
		else if (cmd_info->cmd_args[i][0] == '>' && cmd_info->cmd_args[i][1] == '>')
		{
			type = RIGHT_2;
		}
		i++;
	}
}
