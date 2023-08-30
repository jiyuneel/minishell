/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:54:23 by jiyunlee          #+#    #+#             */
/*   Updated: 2022/11/26 17:16:54 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printf_str(char *str, int *cnt)
{
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		*cnt += 6;
	}
	else
	{
		ft_putstr_fd(str, 1);
		*cnt += ft_strlen(str);
	}
}

static void	print_mem(unsigned long long mem, int *cnt)
{
	if (mem < 16)
	{
		ft_putchar_fd("0123456789abcdef"[mem], 1);
		(*cnt)++;
	}
	else
	{
		print_mem(mem / 16, cnt);
		print_mem(mem % 16, cnt);
	}
}

void	printf_ptr(void *ptr, int *cnt)
{
	ft_putstr_fd("0x", 1);
	*cnt += 2;
	print_mem((unsigned long long) ptr, cnt);
}

void	printf_udeci(unsigned int num, int *cnt)
{
	if (num < 10)
	{
		ft_putchar_fd('0' + num % 10, 1);
		(*cnt)++;
	}
	else
	{
		printf_udeci(num / 10, cnt);
		printf_udeci(num % 10, cnt);
	}
}

void	printf_deci(int num, int *cnt)
{
	long long	n;

	n = num;
	if (num < 0)
	{
		ft_putchar_fd('-', 1);
		(*cnt)++;
		n *= -1;
	}
	printf_udeci(n, cnt);
}
