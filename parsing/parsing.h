/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:08:08 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/09/13 00:29:30 by jiyunlee         ###   ########.fr       */
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

void	env_init(t_env_info **env, char **envp);
void	shell_init(t_shell_info *shell_info, char *str);
void	redir_init(t_cmd_info *cmd_info);

#endif
