/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:39:45 by jiyunlee          #+#    #+#             */
/*   Updated: 2022/11/15 16:07:49 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(int n)
{
	int			len;
	long long	num;

	num = n;
	len = 0;
	if (num <= 0)
	{
		len++;
		num *= -1;
	}
	while (num)
	{
		len++;
		num /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*str;
	long long	num;
	int			i;

	if (n == 0)
		return (ft_strdup("0"));
	str = (char *)malloc(sizeof(char) * numlen(n) + 1);
	if (!str)
		return (NULL);
	num = n;
	i = numlen(n);
	str[i--] = 0;
	if (n < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	while (num)
	{
		str[i--] = '0' + num % 10;
		num /= 10;
	}
	return (str);
}
