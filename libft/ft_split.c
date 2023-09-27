/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:47:43 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/01/30 16:37:56 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	cnt;

	cnt = 0;
	while (*s)
	{
		if (*s != c)
		{
			cnt++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (cnt);
}

static int	wrdlen(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static char	**free_arr(char **arr, int index)
{
	while (index-- > 0)
		free(arr[index]);
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		index;
	int		len;

	arr = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!arr)
		return (NULL);
	index = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = wrdlen(s, c);
			arr[index] = (char *)malloc(sizeof(char) * len + 1);
			if (!arr[index])
				return (free_arr(arr, index));
			ft_strlcpy(arr[index++], s, len + 1);
			s += len;
		}
		else
			s++;
	}
	arr[index] = NULL;
	return (arr);
}
