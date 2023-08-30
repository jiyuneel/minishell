/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:13:37 by jiyunlee          #+#    #+#             */
/*   Updated: 2022/11/21 14:56:45 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp;

	if (!dst && !src)
		return (NULL);
	tmp = (unsigned char *)dst;
	if (dst <= src)
	{
		while (len-- > 0)
			*tmp++ = *(unsigned char *)src++;
	}
	else
	{
		tmp += len - 1;
		src += len - 1;
		while (len-- > 0)
			*tmp-- = *(unsigned char *)src--;
	}
	return (dst);
}
