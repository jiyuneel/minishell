/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 01:00:07 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/13 16:31:51 by jiyunlee         ###   ########.fr       */
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

// void	delete_cmd(t_cmd_info *cmd_info, int idx)
// {
// 	free(cmd_info->cmd_args[idx]);
// 	while (cmd_info->cmd_args[idx])
// 	{
// 		cmd_info->cmd_args[idx] = cmd_info->cmd_args[idx + 1];
// 		idx++;
// 	}
// 	cmd_info->cmd_cnt--;
// }

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

void	redir_init(t_cmd_info *cmd_info)
{
	char			**tmp_args;
	t_token_type	type;
	char			*filename;

	tmp_args = cmd_info->cmd_args;
	while (*tmp_args)
	{
		if ((*tmp_args)[0] == '<' && (*tmp_args)[1] != '<')
		{
			type = LEFT_1;
			if (!(*tmp_args)[1])
			{
				filename = ft_strdup(*(tmp_args + 1));
				delete_cmd(cmd_info, tmp_args + 1);
				delete_cmd(cmd_info, tmp_args);
			}
			else
			{
				filename = malloc(sizeof(char) * ft_strlen(*tmp_args));
				ft_strlcpy(filename, &(*tmp_args)[1], ft_strlen(*tmp_args));
				delete_cmd(cmd_info, tmp_args);
			}
			redir_add_back(&cmd_info->redir, redir_new_node(type, filename));
		}
		else if ((*tmp_args)[0] == '<' && (*tmp_args)[1] == '<')
		{
			type = LEFT_2;
			if (!(*tmp_args)[2])
			{
				filename = ft_strdup(*(tmp_args + 1));
				delete_cmd(cmd_info, tmp_args + 1);
				delete_cmd(cmd_info, tmp_args);
			}
			else
			{
				filename = malloc(sizeof(char) * ft_strlen(*tmp_args) - 1);
				ft_strlcpy(filename, &(*tmp_args)[2], ft_strlen(*tmp_args) - 1);
				delete_cmd(cmd_info, tmp_args);
			}
			redir_add_back(&cmd_info->redir, redir_new_node(type, filename));
		}
		else if ((*tmp_args)[0] == '>' && (*tmp_args)[1] != '>')
		{
			type = RIGHT_1;
			if (!(*tmp_args)[1])
			{
				filename = ft_strdup(*(tmp_args + 1));
				delete_cmd(cmd_info, tmp_args + 1);
				delete_cmd(cmd_info, tmp_args);
			}
			else
			{
				filename = malloc(sizeof(char) * ft_strlen(*tmp_args));
				ft_strlcpy(filename, &(*tmp_args)[1], ft_strlen(*tmp_args));
				delete_cmd(cmd_info, tmp_args);
			}
			redir_add_back(&cmd_info->redir, redir_new_node(type, filename));
		}
		else if ((*tmp_args)[0] == '>' && (*tmp_args)[1] == '>')
		{
			type = RIGHT_2;
			if (!(*tmp_args)[2])
			{
				filename = ft_strdup(*(tmp_args + 1));
				delete_cmd(cmd_info, tmp_args + 1);
				delete_cmd(cmd_info, tmp_args);
			}
			else
			{
				filename = malloc(sizeof(char) * ft_strlen(*tmp_args) - 1);
				ft_strlcpy(filename, &(*tmp_args)[2], ft_strlen(*tmp_args) - 1);
				delete_cmd(cmd_info, tmp_args);
			}
			redir_add_back(&cmd_info->redir, redir_new_node(type, filename));
		}
		else
			tmp_args++;
	}
}

// void	redir_init(t_cmd_info *cmd_info)
// {
// 	int				i;
// 	t_token_type	type;
// 	char			*filename;

// 	i = 0;
// 	while (cmd_info->cmd_args[i])
// 	{
// 		if (cmd_info->cmd_args[i][0] == '<' && cmd_info->cmd_args[i][1] != '<')
// 		{
// 			type = LEFT_1;
// 			if (!cmd_info->cmd_args[i][1])
// 			{
// 				filename = ft_strdup(cmd_info->cmd_args[i + 1]);
// 				delete_cmd(cmd_info, i + 1);
// 				delete_cmd(cmd_info, i);
// 			}
// 			else
// 			{
// 				filename = malloc(sizeof(char) * ft_strlen(cmd_info->cmd_args[i]));
// 				ft_strlcpy(filename, &cmd_info->cmd_args[i][1], ft_strlen(cmd_info->cmd_args[i]));
// 			}
// 			redir_add_back(&cmd_info->redir, redir_new_node(type, filename));
// 		}
// 		else if (cmd_info->cmd_args[i][0] == '<' && cmd_info->cmd_args[i][1] == '<')
// 		{
// 			type = LEFT_2;
// 		}
// 		else if (cmd_info->cmd_args[i][0] == '>' && cmd_info->cmd_args[i][1] != '>')
// 		{
// 			type = RIGHT_1;
// 		}
// 		else if (cmd_info->cmd_args[i][0] == '>' && cmd_info->cmd_args[i][1] == '>')
// 		{
// 			type = RIGHT_2;
// 		}
// 		else
// 			i++;
// 	}
// }
