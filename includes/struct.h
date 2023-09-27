/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 14:14:01 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/28 04:37:39 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <termios.h>

/* macro define*/
# define TRUE	1
# define FALSE	0

/* signal define */
# define DEFAULT	0
# define IGNORE		1
# define JIJI		2
# define HRD_CHILD	3

/* pipe define */
# define P_READ		0
# define P_WRITE	1

/* heredoc define */
# define HERE_DOC	"/tmp/_here_doc_"

/* redirection type */
typedef enum e_token_type
{
	STR = 1,
	PIPE,
	LEFT_1,
	LEFT_2,
	RIGHT_1,
	RIGHT_2
}	t_token_type;

/* [shared data] */
/* parse -> execute: static variable */
typedef struct s_shell_info
{
	int					chunk_cnt;
	int					heredoc_cnt;
	struct s_env_info	*env;
	struct s_cmd_info	*cmd;
	struct termios		origin_term;
}	t_shell_info;

/* struct for cmd_node */
typedef struct s_cmd_info
{
	int					cmd_cnt;
	char				**cmd_args;
	struct s_str		*str;
	struct s_redir		*redir;
	struct s_cmd_info	*next;
}	t_cmd_info;

/* struct for str */
typedef struct s_str
{
	t_token_type	type;
	char			*command;
	struct s_str	*next;
}	t_str;

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
	int					idx;
	struct s_env_info	*next;
}	t_env_info;

/* [parsing.c data] */
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				valid;
	struct s_token	*next;
}	t_token;

typedef struct s_quote
{
	int		quote_flag;
	char	quote;
}	t_quote;

/* [execute.c data] */
typedef struct s_exec_info
{
	int					in_fd;
	int					out_fd;
	int					pipe[2];
	char				**cmd_args;
	char				**path_args;
	char				**envp;
	struct s_env_info	**env;
	struct termios		origin_term;
}	t_exec_info;

#endif
