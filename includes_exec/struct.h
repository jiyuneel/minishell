/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 18:47:57 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/13 04:59:08 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define P_READ		0
# define P_WRITE	1

# define HERE_DOC	"._here_doc_"

typedef struct s_exec_info
{
	// node 마다 값이 reset될 수 있음
	int		here_doc;		// here_doc flags
	int		in_fd;
	int		out_fd;
	int		pipe[2];
	char	**cmd_args;		// t_shell_info의 cmd_args 그대로 복사한 주소 >> free 따로 안함

	// 한 줄 실행이 모두 끝나면 free
	char	**path_args;	// t_env_info의 key-PATH의 value 값 ':'로 split
	char	**envp;			// t_env_info를 다시 '='과 합친 이중 배열(for 'execve')
	t_env_info	*env;			// t_env_info 값 그대로 복사한 주소 >> free 따로 안함
}	t_exec_info;


#endif
