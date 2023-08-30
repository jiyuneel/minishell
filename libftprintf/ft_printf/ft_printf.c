/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:42:59 by jiyunlee          #+#    #+#             */
/*   Updated: 2022/11/26 19:11:04 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	check_specifier(va_list ap, const char *format, int *cnt)
{
	if (*format == 'c')
	{
		ft_putchar_fd(va_arg(ap, int), 1);
		(*cnt)++;
	}
	else if (*format == 's')
		printf_str(va_arg(ap, char *), cnt);
	else if (*format == 'p')
		printf_ptr(va_arg(ap, void *), cnt);
	else if (*format == 'd' || *format == 'i')
		printf_deci(va_arg(ap, int), cnt);
	else if (*format == 'u')
		printf_udeci(va_arg(ap, int), cnt);
	else if (*format == 'x')
		printf_hexa(va_arg(ap, int), cnt, 0);
	else if (*format == 'X')
		printf_hexa(va_arg(ap, int), cnt, 1);
	else if (*format == '%')
	{
		ft_putchar_fd('%', 1);
		(*cnt)++;
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		cnt;

	va_start(ap, format);
	cnt = 0;
	while (*format)
	{
		if (*format == '%')
			check_specifier(ap, ++format, &cnt);
		else
		{
			ft_putchar_fd(*format, 1);
			cnt++;
		}
		format++;
	}
	va_end(ap);
	return (cnt);
}
