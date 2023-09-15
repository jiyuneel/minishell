/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:57:23 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/15 15:50:45 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libftprintf/libft/libft.h"
# include "../libftprintf/ft_printf/ft_printf.h"
# include "../libftprintf/get_next_line/get_next_line.h"
// # include "../includes_exec/execute.h"
// # include "../parsing/parsing.h"

# define TRUE	1
# define FALSE	0

/* signal define */
# define SHELL		0
# define DEFAULT	1
# define IGNORE		2

/* global variable: exit code */
extern int	g_exit_code;

/* redirection type */
typedef enum e_token_type
{
	LEFT_1 = 1,		// <
	LEFT_2,			// <<
	RIGHT_1,		// >
	RIGHT_2			// >>
}	t_token_type;

/* [ parse -> execute ]: no alloc variable */
typedef struct s_shell_info
{
	int					chunk_cnt;	// count of nodes
	struct s_env_info	*env;		// env head
	struct s_cmd_info	*cmd;		// cmd head
}	t_shell_info;

/* struct for cmd_node */
typedef struct s_cmd_info
{
	int					cmd_cnt;		// count of commands
	char				**cmd_args;		// array of commands
	struct s_redir		*redir;			// redirection head
	struct s_cmd_info	*next;
}	t_cmd_info;

/* struct for redirections */
typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

/* struct for env */
typedef struct s_env_info
{
	char				*key;
	char				*value;
	struct s_env_info	*next;
}	t_env_info;

#endif
