/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_invalid_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:29:19 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/18 15:39:03 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

int		only_space(char *str);
void	delete_token(t_token **token, t_token **node);

void	delete_invalid_token(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (!tmp->valid || only_space(tmp->value))
			delete_token(token, &tmp);
		else
			tmp = tmp->next;
	}
}

int	only_space(char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

void	delete_token(t_token **token, t_token **node)
{
	t_token	*prev;

	if (*node == *token)
	{
		*token = (*token)->next;
		free((*node)->value);
		free(*node);
		*node = *token;
	}
	else
	{
		prev = *token;
		while (prev->next != *node)
			prev = prev->next;
		prev->next = (*node)->next;
		free((*node)->value);
		free(*node);
		*node = prev->next;
	}
}
