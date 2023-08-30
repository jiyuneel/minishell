/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:12:55 by jiyunlee          #+#    #+#             */
/*   Updated: 2022/11/14 20:44:40 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_issubset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_issubset(s1[start], set))
		start++;
	while (ft_issubset(s1[end], set))
		end--;
	if (start <= end)
	{
		str = (char *)malloc(sizeof(char) * (end - start + 1) + 1);
		if (!str)
			return (0);
		ft_strlcpy(str, s1 + start, end - start + 2);
		return (str);
	}
	else
		return (ft_strdup(""));
}
