# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiyunlee <jiyunlee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/24 18:39:56 by jiyunlee          #+#    #+#              #
#    Updated: 2023/08/11 15:14:54 by jiyunlee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRCS	= ft_printf/ft_printf.c	\
		  ft_printf/ft_printf_utils.c \
		  ft_printf/ft_printf_utils2.c
OBJS	= ${SRCS:.c=.o}

LIBFT	= ./libft/libft.a

NAME	= libftprintf.a

all: ${NAME}

${NAME}: ${OBJS}
	@make -C ./libft
	@cp ${LIBFT} ${NAME}
	@ar rc ${NAME} ${OBJS}

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@make -C ./libft fclean
	@rm -f ${OBJS}

fclean: clean
	@rm -f ${NAME}

re:	fclean all

.PHONY: all clean fclean re
