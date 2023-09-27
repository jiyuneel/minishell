/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:18:20 by jiyunlee          #+#    #+#             */
/*   Updated: 2022/11/15 17:30:15 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_nbr(long long n, int fd)
{
	if (n)
	{
		print_nbr(n / 10, fd);
		ft_putchar_fd('0' + n % 10, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	num;

	num = n;
	if (n == 0)
		ft_putchar_fd('0', fd);
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		num *= -1;
	}
	print_nbr(num, fd);
}
