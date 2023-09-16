/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:08:08 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/16 14:17:48 by jiyunlee         ###   ########.fr       */
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

// execute 넘기기 전에 free해야 함
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

void	env_init(t_env_info **env, char **envp);
void	shell_init(t_shell_info *shell_info, char *str);
void	redir_init(t_cmd_info *cmd_info);
void	parse_by_pipe(t_token **token, char *str);
char	**parse_by_redir(char *str);
void	check_quote(int *quote_flag, char *quote, char c);
void	free_token(t_token *token);

#endif
