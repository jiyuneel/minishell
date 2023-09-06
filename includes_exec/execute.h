/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:45:22 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/06 22:26:46 by jihykim2         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>

/* [ function prototype ] */
/* execute.c */
int		execute(t_shell_info *parse);

/* multi_process.c */
void	parent_process(t_exec_info *exec);
void	child_process(t_exec_info *exec, t_cmd_info *node);

/* set_redir.c */
void	dup_redir_to_inout(t_exec_info *exec, t_redir *redir);


#endif
