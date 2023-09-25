/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 14:14:01 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/25 16:30:15 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/* macro define*/
# define TRUE	1
# define FALSE	0

/* signal define */
# define DEFAULT	0		// original-shell
# define IGNORE		1
# define JIJI		2		// our jiji-shell (exec-process)
# define HRD_CHILD	3		// in here_doc process

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
	LEFT_1,			// <
	LEFT_2,			// <<
	RIGHT_1,		// >
	RIGHT_2			// >>
}	t_token_type;

/* [shared data] */
/* parse -> execute: static variable */
typedef struct s_shell_info
{
	int					chunk_cnt;	// count of nodes
	struct s_env_info	*env;		// env head
	struct s_cmd_info	*cmd;		// cmd head
	int					heredoc_cnt;
}	t_shell_info;

/* struct for cmd_node */
typedef struct s_cmd_info
{
	int					cmd_cnt;		// count of commands
	char				**cmd_args;		// array of commands
	struct s_str		*str;
	struct s_redir		*redir;			// redirection head
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
/* struct for exec */
typedef struct s_exec_info
{
	int					here_doc;		// flag
	int					in_fd;
	int					out_fd;
	int					pipe[2];
	char				**cmd_args;		// copy address
	char				**path_args;	// free(needed)
	char				**envp;			// free(needed)
	struct s_env_info	**env;			// copy address
}	t_exec_info;

#endif
