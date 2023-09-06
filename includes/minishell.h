/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:57:23 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/06 17:36:56 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libftprintf/libft/libft.h"
# include "../libftprintf/ft_printf/ft_printf.h"
# include "../libftprintf/get_next_line/get_next_line.h"

# define TRUE	1
# define FALSE	0

typedef enum e_token_type
{
	CMD_ARG = 0,	// word
	LEFT_1,			// <
	LEFT_2,			// <<
	RIGHT_1,		// >
	RIGHT_2			// >>
}	t_token_type;

/* [ parse -> execute ]: no alloc variable */
typedef struct s_shell_info
{
	int					pipe_cnt;	// pipe 개수
	struct s_env_info	*env;
	struct s_cmd_info	*cmd_node;	// cmd head -> execute 에서 다 free하고 넘길 것
}	t_shell_info;

typedef struct s_cmd_info
{
	int					cmd_cnt;		// 명령 단위 개수
	char				**cmd_args;		// 마지막은 NULL
	t_token_type		*cmd_type;		// token type 배열
	struct s_cmd_info	*next;
}	t_cmd_info;

typedef struct s_env_info
{
	char				*key;
	char				*value;
	struct s_env_info	*next;
}	t_env_info;



#endif
