/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:45:22 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/07 15:12:43 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../includes/minishell.h"
# include "./struct.h"

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <term.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>

/* [ function prototype ] */
/* execute.c */
int			execute(t_shell_info *parse);

/* init_exec_info.c */
t_exec_info	*init_exec_info(t_shell_info *parse);

/* multi_process.c */
void		parent_process(t_exec_info *exec);
void		child_process(t_exec_info *exec, t_cmd_info *node);

/* set_redir.c */
void		dup_redir_to_inout(t_exec_info *exec, t_redir *redir);

/* exec_command.c */
void		exec_command(t_exec_info *exec);

#endif
