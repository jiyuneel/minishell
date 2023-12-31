# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/30 20:04:18 by jiyunlee          #+#    #+#              #
#    Updated: 2023/08/30 21:07:40 by jiyunlee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
JIYUN		= jiyun
JIHYUN		= jihyun

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

LIB_DIR		= ./libftprintf

SRCS_YUN	= test.c
OBJS_YUN	= $(SRCS_YUN:.c=.o)

SRCS_HYUN	= 
OBJS_HYUN	= $(SRCS_HYUN:.c=.o)

SRCS		= test2.c
OBJS		= $(SRCS:.c=.o)

# ifdef JIYUN
# 	OBJ = $(OBJS_YUN)
# else ifdef JIHYUN
# 	OBJ = $(OBJS_HYUN)
# else
# 	OBJ = $(OBJS)
# endif


all		: $(NAME)
jiyun	: $(JIYUN)
jihyun	: $(JIHYUN)

%.o		: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	: $(OBJS)
	@$(MAKE) -C $(LIB_DIR)
	@echo $(YELLOW) "✭	[ libftprintf ]	Ready to use libftprintf.a" $(RESET)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIB_DIR) -lftprintf
	@echo $(GREEN) "⚡︎	[ minishell ]	Ready to use minishell" $(RESET)

# jiyun	:
# 	@$(MAKE) JIYUN=1 all

# jihyun	:
# 	@$(MAKE) JIHYUN=1 all

$(JIYUN): $(OBJS_YUN)
	@$(MAKE) -C $(LIB_DIR)
	@echo $(YELLOW) "✭	[ libftprintf ]	Ready to use libftprintf.a" $(RESET)
	@$(CC) $(CFLAGS) -o $(JIYUN) $(OBJS_YUN) -L$(LIB_DIR) -lftprintf
	@echo $(GREEN) "⚡︎	[ JIYUN ]	Ready to run jiyunlee" $(RESET)

$(JIHYUN): $(OBJS_HYUN)
	@$(MAKE) -C $(LIB_DIR)
	@echo $(YELLOW) "✭	[ libftprintf ]	Ready to use libftprintf.a" $(RESET)
	@$(CC) $(CFLAGS) -o $(JIHYUN) $(OBJS_HYUN) -L$(LIB_DIR) -lftprintf
	@echo $(GREEN) "⚡︎	[ JIHYUN ]	Ready to run jihykim2" $(RESET)


clean	:
	@$(MAKE) -C $(LIB_DIR) clean
	@echo $(YELLOW) "✭	[ libftprintf ]	Removed Object files" $(RESET)
	@$(RM) $(OBJS) $(OBJS_YUN) $(OBJS_HYUN)
	@echo $(GREEN) "⚡︎	[ minishell ]	Removed Object files" $(RESET)
#	@$(RM) $(OBJS)

fclean	: clean
	@$(MAKE) -C $(LIB_DIR) fclean
	@echo $(YELLOW) "✭	[ libftprintf ]	Removed libftprintf.a" $(RESET)
	@$(RM) $(NAME) $(JIYUN) $(JIHYUN)
	@echo $(GREEN) "⚡︎	[ minishell ]	Removed minishell" $(RESET)

re		:
	@$(MAKE) fclean
	@$(MAKE) all

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
