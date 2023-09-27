/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:57:23 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/27 09:52:44 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* global variable: exit code */
extern int	g_exit_code;

# include "./struct.h"
# include "../libftprintf/libft/libft.h"
# include "../libftprintf/ft_printf/ft_printf.h"
# include "../libftprintf/get_next_line/get_next_line.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <term.h>
# include <sys/termios.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <fcntl.h>

/* [parsing] */
/* env_init.c */
void		env_init(t_env_info **env, char **envp);

/* shell_init.c */
int			shell_init(t_shell_info *shell_info, char *str);

/* cmd_init.c */
void		cmd_init(t_cmd_info **cmd, t_token *token);
void		cmd_args_init(t_shell_info *shell_info, t_cmd_info *cmd);

/* parse_by_pipe.c */
void		parse_by_pipe(t_token **token, char *str);
/* parse_by_redir.c */
void		parse_by_redir(t_token **token);
/* parse_by_space.c */
void		parse_by_space(t_token **token);

/* delete_invalid_token.c */
void		delete_invalid_token(t_token **token);

/* handle_syntax_error.c */
int			check_quote(t_quote	*q, char c);
int			handle_syntax_error(t_shell_info *shell_info, t_token *token, char *str);

/* replace_env.c */
void		replace_env(t_env_info *env, t_token *token);
void		get_env_value(t_env_info *env, t_env_info *env_var);
t_env_info	*tmpenv_new_node(char *key, int idx);

/* t_env_func.c */
t_env_info	*env_new_node(char *key, char *value);
void		env_add_back(t_env_info **node, t_env_info *new);
void		env_add_front(t_env_info **node, t_env_info *new);

/* t_token_func.c */
t_token		*token_new_node(t_token_type type, char *value);
void		token_add_back(t_token **node, t_token *new);
void		free_token(t_token *token);

/* t_str_func.c */
t_str		*str_new_node(char *command);
void		str_add_back(t_str **node, t_str *new);
void		free_str(t_str *str);

/* t_redir_func.c */
t_redir		*redir_new_node(t_token_type type, char *filename);
void		redir_add_back(t_redir **node, t_redir *new);
void		free_redir(t_redir *redir);


/* [execute] */
/* execute.c */
void		execute(t_shell_info *parse);

/* set_signal.c */
void		set_signal(int sig_int, int sig_quit);

/* re_init_shell_info.c */
int			re_init_shell_info(t_shell_info *parse);

/* line_replace_env.c */
char		*line_replace_env(t_env_info *env, char *str);

/* remove_quotation.c */
char		*remove_quotation(char *command, int origin_len);

/* init_exec_info.c */
t_exec_info	*init_exec_info(t_shell_info *parse);

/* single_process.c */
int			single_process(t_exec_info *exec, t_cmd_info *cmd);

/* multi_process.c */
void		multi_process(t_exec_info *exec, t_cmd_info *cmd, int chunk_cnt);

/* wait_child.c */
void		wait_child(pid_t last_pid, int chunk_cnt);

/* exec_command.c */
void		exec_command(t_exec_info *exec);

/* unlink_here_doc.c */
void		unlink_here_doc(t_cmd_info *cmd);

/* error_exit.c */
void		error_file_open(char *filename);
void		error_for_dot(char *cmd, int len);
void		error_no_auth(char *cmd);
void		error_exit(char *cmd, int sys_errno);


/* [built-in] */
int			is_builtin(t_exec_info *exec, int *exit_code);
int			echo(t_exec_info *exec);
int			cd(t_exec_info *exec);
int			pwd(t_exec_info *exec);
int			export(t_exec_info *exec);
int			unset(t_exec_info *exec);
int			env(t_exec_info *exec);
int			exit_with_args(t_exec_info *exec);
void		delete_env(t_env_info **env, t_env_info **node);

/* [utils] */
/* free_all.c */
void		free_cmd_info(t_cmd_info *cmd, int heredoc_cnt);
void		free_env_info(t_env_info *env);
void		free_exec_info(t_exec_info *exec);
void		free_arr(char **arr);

/* set_redir.c */
void		dup_redir_to_inout(t_exec_info *exec, t_redir *redir);

#endif
