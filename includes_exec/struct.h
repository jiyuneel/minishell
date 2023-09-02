/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 18:47:57 by jihykim2          #+#    #+#             */
/*   Updated: 2023/09/02 19:57:06 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/* [DEAR. pasing]
 * redirection 개수가 있었으면 좋겠음: cmd_type 배열을 다 돌아봐야 함
 */

typedef struct s_exec_info
{
	// node 마다 값이 reset될 수 있음
	int		here_doc;		// here_doc flags
	int		in_fd;
	int		out_fd;
	int		pipe[2];
	char	**cmd_args;		// node 당 type이 cmd인것만 pasing하고 free

	// 일단 받아온 인자 자체로 사용하기 -> pasing 이후엔 해당 값(key-value) 사용
	// 이 경우, 따로 free 안해도 됨
	char	**envp;			// t_env_info의 head 주소
	char	**path_args;	// t_env_info의 key-PATH의 value 값 주소
}	t_exec_info;


#endif
