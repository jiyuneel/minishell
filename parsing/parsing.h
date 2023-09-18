/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:08:08 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/18 15:41:01 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../includes/minishell.h"
# include <stdio.h>	/* readline 하려면 필요 */
# include <readline/readline.h>
# include <readline/history.h>
# include "../includes_exec/execute.h"

typedef struct s_quote
{
	int		quote_flag;
	char	quote;
}	t_quote;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				valid;
	struct s_token	*next;
}	t_token;

/* struct for str */
typedef struct s_str
{
	t_token_type	type;
	char			*command;
	struct s_str	*next;
}	t_str;

/* env_init.c */
void	env_init(t_env_info **env, char **envp);

/* shell_init.c */
int		shell_init(t_shell_info *shell_info, char *str);

/* handle_syntax_error.c */
void	check_quote(int *quote_flag, char *quote, char c);
int		handle_syntax_error(t_token *token, char *str);

/* parse_by_pipe.c */
void	parse_by_pipe(t_token **token, char *str);
/* parse_by_redir.c */
void	parse_by_redir(t_token **token);
/* parse_by_space.c */
void	parse_by_space(t_token **token);

/* delete_invalid_token.c */
void	delete_invalid_token(t_token **token);

/* t_token_func.c */
t_token	*token_new_node(t_token_type type, char *value);
void	token_add_back(t_token **node, t_token *new);
void	free_token(t_token *token);

/* t_str_func.c */
t_str	*str_new_node(char *command);
void	str_add_back(t_str **node, t_str *new);

/* t_redir_func.c */
t_redir	*redir_new_node(t_token_type type, char *filename);
void	redir_add_back(t_redir **node, t_redir *new);

#endif
