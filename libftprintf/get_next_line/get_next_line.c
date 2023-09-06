/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:04:25 by jihykim2          #+#    #+#             */
/*   Updated: 2023/07/15 18:38:44 by jihykim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_info	*find_fd(t_info **head, int new_fd);
static size_t	read_file(t_info *lst);
static char		*cut_next_line(t_info **head, t_info *lst, size_t gnl_len);

char	*get_next_line(int fd)
{
	static t_info	*head;
	t_info			*lst;
	size_t			gnl_len;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	lst = find_fd(&head, fd);
	if (lst == NULL)
		return (NULL);
	gnl_len = read_file(lst);
	if (gnl_len == 0)
		return (free_all(&head, lst));
	lst->buff[lst->len] = '\0';
	return (cut_next_line(&head, lst, gnl_len));
}

static t_info	*find_fd(t_info **head, int new_fd)
{
	t_info	*tmp;

	if (*head == NULL)
		*head = gnl_lstnew(new_fd);
	tmp = *head;
	while (tmp)
	{
		if (tmp->fd == new_fd)
			return (tmp);
		if (tmp->next == NULL)
			tmp->next = gnl_lstnew(new_fd);
		tmp = tmp->next;
	}
	return (NULL);
}

static size_t	read_file(t_info *lst)
{
	ssize_t	readsize;

	while (check_newline(lst->buff) == 0)
	{
		if (lst->len + BUFFER_SIZE > lst->b_size && realloc_backup(lst) == NULL)
			return (0);
		readsize = read(lst->fd, lst->buff + lst->len, BUFFER_SIZE);
		if (readsize < 0)
			return (0);
		else if (readsize == 0)
			return (lst->len);
		lst->len += readsize;
		lst->buff[lst->len] = '\0';
	}
	return (check_newline(lst->buff));
}

static char	*cut_next_line(t_info **head, t_info *lst, size_t gnl_len)
{
	char	*gnl;
	char	*tmp;

	gnl = malloc(sizeof(char) * (gnl_len + 1));
	if (gnl == NULL)
		return (free_all(head, lst));
	gnl_strlcpy(gnl, lst->buff, gnl_len + 1);
	tmp = lst->buff;
	lst->len = lst->len - gnl_len;
	while (lst->len < lst->b_size / 2)
		lst->b_size /= 2;
	lst->buff = malloc(sizeof(char) * (lst->b_size + 1));
	if (lst->buff == NULL)
	{
		free (gnl);
		free (tmp);
		return (free_all(head, lst));
	}
	if (gnl_strlcpy(lst->buff, tmp + gnl_len, lst->len + 1) == 0)
		free_all(head, lst);
	free (tmp);
	return (gnl);
}
