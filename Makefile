# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/30 20:04:18 by jiyunlee          #+#    #+#              #
#    Updated: 2023/09/01 16:23:05 by jiyunlee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

LIB_DIR		= ./libftprintf

YUN_DIR		= ./parsing/
SRCS_Y		= minishell.c	env_init.c
SRCS_YUN	= $(addprefix $(YUN_DIR), $(SRCS_Y))
OBJS_YUN	= $(SRCS_YUN:.c=.o)

SRCS_HYUN	=
OBJS_HYUN	= $(SRCS_HYUN:.c=.o)

SRCS		=
OBJS		= $(SRCS:.c=.o)

ifdef JIYUN
	OBJ = $(OBJS_YUN)
else ifdef JIHYUN
	OBJ = $(OBJS_HYUN)
else
	OBJ = $(OBJS)
endif

all		: $(NAME)

%.o		: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	: $(OBJ)
	@$(MAKE) -C $(LIB_DIR)
	@echo $(YELLOW) "✭	[ libftprintf ]	Ready to use libftprintf.a" $(RESET)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIB_DIR) -lftprintf
	@echo $(GREEN) "⚡︎	[ minishell ]	Ready to use minishell" $(RESET)

jiyun	:
	@$(MAKE) JIYUN=1 all

jihyun	:
	@$(MAKE) JIHYUN=1 all

clean	:
	@$(MAKE) -C $(LIB_DIR) clean
	@echo $(YELLOW) "✭	[ libftprintf ]	Removed Object files" $(RESET)
	@$(RM) $(OBJS) $(OBJS_YUN) $(OBJS_HYUN)
	@echo $(GREEN) "⚡︎	[ minishell ]	Removed Object files" $(RESET)

fclean	: clean
	@$(MAKE) -C $(LIB_DIR) fclean
	@echo $(YELLOW) "✭	[ libftprintf ]	Removed libftprintf.a" $(RESET)
	@$(RM) $(NAME)
	@echo $(GREEN) "⚡︎	[ minishell ]	Removed minishell" $(RESET)

re		:
	@$(MAKE) fclean
	@$(MAKE) jiyun

.PHONY	: all clean fclean re jiyun jihyun

RESET	= "\x1b[0m"
GREY	= "\x1b[30m"
RED		= "\x1b[31m"
GREEN	= "\x1b[32m"
YELLOW	= "\x1b[33m"
BLUE	= "\x1b[34m"
PURPLE	= "\x1b[35m"
CYAN	= "\x1b[36m"
WHITE	= "\x1b[37m"
