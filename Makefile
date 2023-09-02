# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/30 20:04:18 by jiyunlee          #+#    #+#              #
#    Updated: 2023/09/02 21:46:09 by jihykim2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

LIB_DIR		= ./libftprintf

SRCS_YUN	=
OBJS_YUN	= $(SRCS_YUN:.c=.o)

# [start] 여기만 바꿀 수 있음!!
HYUN_DIR	= ./execute/
SRCS_HYUN	= execute.c
			  init_exec_info.c
OBJS_HYUN	= $(addprefix $(HYUN_DIR), $(SRCS_HYUN:.c=.o))
# [end]

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
	@$(MAKE) jihyun
# 여기 위에도 바꿈!! -> 다시 원상복귀 할 것

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
