/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:51:01 by jiyunlee          #+#    #+#             */
/*   Updated: 2022/11/21 14:57:59 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstlen;

	dstlen = ft_strlen(dst);
	if (dstlen >= dstsize)
		return (dstsize + ft_strlen(src));
	while (*dst)
		dst++;
	i = 0;
	while (src[i] && i < dstsize - dstlen - 1)
		*dst++ = src[i++];
	*dst = 0;
	return (dstlen + ft_strlen(src));
}
