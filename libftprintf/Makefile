# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/24 18:39:56 by jiyunlee          #+#    #+#              #
#    Updated: 2023/09/17 06:45:43 by jihykim2         ###   ########.fr        #
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
	@echo $(YELLOW) "✭	[ libftprintf ]	Ready to use libftprintf.a" $(RESET)

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@make -C ./libft fclean
	@rm -f ${OBJS}

fclean: clean
	@rm -f ${NAME}

re:	fclean all

.PHONY: all clean fclean re

RESET	= "\x1b[0m"
GREY	= "\x1b[30m"
RED		= "\x1b[31m"
GREEN	= "\x1b[32m"
YELLOW	= "\x1b[33m"
BLUE	= "\x1b[34m"
PURPLE	= "\x1b[35m"
CYAN	= "\x1b[36m"
WHITE	= "\x1b[37m"
