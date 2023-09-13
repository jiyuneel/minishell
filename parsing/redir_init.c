/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 01:00:07 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/13 20:07:06 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_redir	*redir_new_node(t_token_type type, char *filename)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->type = type;
    node->filename = filename;
	node->next = NULL;
	return (node);
}

void	redir_add_back(t_redir **node, t_redir *new)
{
	t_redir	*tmp;

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

void	delete_cmd(t_cmd_info *cmd_info, char **cmd)
{
	free(*cmd);
	while (*cmd)
	{
		*cmd = *(cmd + 1);
		cmd++;
	}
	cmd_info->cmd_cnt--;
}

char	*set_redir_filename(t_cmd_info *cmd_info, char **args, t_token_type type)
{
	char	*filename;

	filename = NULL;
	if ((type == LEFT_1 || type == RIGHT_1) && !(*args)[1])
	{
		filename = ft_strdup(*(args + 1));
		delete_cmd(cmd_info, args + 1);
	}
	else if ((type == LEFT_1 || type == RIGHT_1) && (*args)[1])
	{
		filename = malloc(sizeof(char) * ft_strlen(*args));
		ft_strlcpy(filename, &(*args)[1], ft_strlen(*args));
	}
	else if ((type == LEFT_2 || type == RIGHT_2) && !(*args)[2])
	{
		filename = ft_strdup(*(args + 1));
		delete_cmd(cmd_info, args + 1);
	}
	else if ((type == LEFT_2 || type == RIGHT_2) && (*args)[2])
	{
		filename = malloc(sizeof(char) * ft_strlen(*args) - 1);
		ft_strlcpy(filename, &(*args)[2], ft_strlen(*args) - 1);
	}
	delete_cmd(cmd_info, args);
	return (filename);
}

void	redir_init(t_cmd_info *cmd_info)
{
	char			**tmp_args;
	t_token_type	type;
	char			*filename;

	tmp_args = cmd_info->cmd_args;
	while (*tmp_args)
	{
		if ((*tmp_args)[0] == '<' || (*tmp_args)[0] == '>')
		{
			if ((*tmp_args)[0] == '<' && (*tmp_args)[1] != '<')
				type = LEFT_1;
			else if ((*tmp_args)[0] == '<' && (*tmp_args)[1] == '<')
				type = LEFT_2;
			else if ((*tmp_args)[0] == '>' && (*tmp_args)[1] != '>')
				type = RIGHT_1;
			else if ((*tmp_args)[0] == '>' && (*tmp_args)[1] == '>')
				type = RIGHT_2;
			filename = set_redir_filename(cmd_info, tmp_args, type);
			redir_add_back(&cmd_info->redir, redir_new_node(type, filename));
		}
		else
			tmp_args++;
	}
}
