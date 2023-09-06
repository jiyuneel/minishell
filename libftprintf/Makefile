# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/24 18:39:56 by jiyunlee          #+#    #+#              #
#    Updated: 2023/09/06 17:35:30 by jihykim2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRCS	= ft_printf/ft_printf.c	\
		  ft_printf/ft_printf_utils.c \
		  ft_printf/ft_printf_utils2.c \
		  get_next_line/get_next_line.c \
		  get_next_line/get_next_line_utils.c
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
