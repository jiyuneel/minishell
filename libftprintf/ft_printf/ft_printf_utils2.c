/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:12:47 by jiyunlee          #+#    #+#             */
/*   Updated: 2022/11/26 17:34:05 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_lowhexa(unsigned int num, int *cnt)
{
	if (num < 16)
	{
		ft_putchar_fd("0123456789abcdef"[num], 1);
		(*cnt)++;
	}
	else
	{
		print_lowhexa(num / 16, cnt);
		print_lowhexa(num % 16, cnt);
	}
}

static void	print_uphexa(unsigned int num, int *cnt)
{
	if (num < 16)
	{
		ft_putchar_fd("0123456789ABCDEF"[num], 1);
		(*cnt)++;
	}
	else
	{
		print_uphexa(num / 16, cnt);
		print_uphexa(num % 16, cnt);
	}
}

void	printf_hexa(int num, int *cnt, int up)
{
	if (up)
		print_uphexa(num, cnt);
	else
		print_lowhexa(num, cnt);
}
