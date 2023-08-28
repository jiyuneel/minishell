/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:57:23 by jihykim2          #+#    #+#             */
/*   Updated: 2023/08/28 22:05:19 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef enum e_token_type
{
	CMD_ARG = 0,	// word
	LEFT_1,			// <
	LEFT_2,			// <<
	RIGHT_1,		// >
	RIGHT_2			// >>
}	t_token_type;

typedef struct s_shell_info
{
	int					pipe_cnt;
	// env head
	struct s_cmd_info	*cmd_node;	// cmd head
}	t_shell_info;

typedef struct s_cmd_info
{
	int			cmd_cnt;
	char		**cmd_args;
	t_token_type	*cmd_type;
}	t_cmd_info;



#endif
