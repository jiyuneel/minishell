/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:04:55 by jihykim2          #+#    #+#             */
/*   Updated: 2023/02/11 15:21:21 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef DEFAULT_SIZE
#  if BUFFER_SIZE < 1024
#   define DEFAULT_SIZE 1024
#  else
#   define DEFAULT_SIZE BUFFER_SIZE
#  endif
# endif

typedef struct s_info
{
	int				fd;
	char			*buff;
	size_t			len;
	size_t			b_size;
	struct s_info	*next;
}	t_info;

char	*get_next_line(int fd);

void	*free_all(t_info **head, t_info *lst);
t_info	*gnl_lstnew(int new_fd);
size_t	check_newline(char *s);
char	*realloc_backup(t_info *lst);
size_t	gnl_strlcpy(char *dst, const char *src, size_t size);

#endif
