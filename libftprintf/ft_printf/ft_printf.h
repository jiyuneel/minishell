/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunlee <jiyunlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:38:40 by jiyunlee          #+#    #+#             */
/*   Updated: 2023/08/06 12:43:44 by jiyunlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>

int		ft_printf(const char *format, ...);
void	printf_str(char *str, int *cnt);
void	printf_ptr(void *ptr, int *cnt);
void	printf_deci(int n, int *cnt);
void	printf_udeci(unsigned int num, int *cnt);
void	printf_hexa(int num, int *cnt, int up);

#endif
