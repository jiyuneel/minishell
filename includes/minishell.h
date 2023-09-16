/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:57:23 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/16 14:45:48 by jihykim2         ###   ########.fr       */
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
# include <dirent.h>
# include <term.h>
# include <sys/termios.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <fcntl.h>

/* [parsing] */
void	env_init(t_env_info **env, char **envp);
void	shell_init(t_shell_info *shell_info, char *str);
void	redir_init(t_cmd_info *cmd_info);


/* [execute] */
/* execute.c */
void		execute(t_shell_info *parse);

/* set_signal.c */
void		set_signal(int sig_int, int sig_quit);

/* re_init_shell_info.c */
int			re_init_shell_info(t_shell_info *parse);

/* remove_quotation.c */
char		*remove_quotation(char *command, int origin_len);

/* init_exec_info.c */
t_exec_info	*init_exec_info(t_shell_info *parse);

/* multi_process.c */
void		multi_process(t_exec_info *exec, t_cmd_info *cmd, int chunk_cnt);

/* set_redir.c */
void		dup_redir_to_inout(t_exec_info *exec, t_redir *redir);

/* exec_command.c */
void		exec_command(t_exec_info *exec);

/* free_all.c */
void		free_cmd_info(t_cmd_info *cmd);
void		free_redir(t_redir *redir);
void		free_env_info(t_env_info *env);
void		free_exec_info(t_exec_info *exec);
void		free_arr(char **arr);

/* unlink_here_doc.c */
void		unlink_here_doc(t_cmd_info *cmd);

/* error_exit.c */
void		error_file_open(char *filename);
void		error_exit(char *cmd, int sys_errno);

#endif
