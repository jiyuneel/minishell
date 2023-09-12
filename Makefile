# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihykim2 <jihykim2@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/30 20:04:18 by jiyunlee          #+#    #+#              #
#    Updated: 2023/09/13 05:35:38 by jihykim2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror #-fsanitize=address -g2
COMP_FLAGS	= -L/opt/homebrew/opt/readline/lib -lreadline
OBJS_FLAGS	= -I/opt/homebrew/opt/readline/include
COMP_FLAGS_CLUSTER = -L/usr/local/lib -lreadline
OBJS_FLAGS_CLUSTER = -I/usr/local/include/readline
RM			= rm -f

LIB_DIR		= ./libftprintf

YUN_DIR		= ./parsing/
SRCS_YUN	= minishell.c	env_init.c	shell_init.c
OBJS_YUN	= $(addprefix $(YUN_DIR), $(SRCS_YUN:.c=.o))

HYUN_DIR	= ./execute/
SRCS_HYUN	= execute.c \
			  re_init_shell_info.c \
			  remove_quotation.c \
			  init_exec_info.c \
			  multi_process.c \
			  set_redir.c \
			  exec_command.c \
			  free_all.c \
			  unlink_here_doc.c
OBJS_HYUN	= $(addprefix $(HYUN_DIR), $(SRCS_HYUN:.c=.o))

SRCS		= $(SRCS_YUN) $(SRCS_HYUN)
OBJS		= $(OBJS_YUN) $(OBJS_HYUN)

ifdef JIYUN
	OBJ = $(OBJS_YUN)
else ifdef JIHYUN
	OBJ = $(OBJS_HYUN)
else
	OBJ = $(OBJS)
endif

all		: $(NAME)

%.o		: %.c
	@$(CC) $(CFLAGS) $(OBJS_FLAGS_CLUSTER) -c $< -o $@

$(NAME)	: $(OBJ)
	@$(MAKE) -C $(LIB_DIR)
	@echo $(YELLOW) "✭	[ libftprintf ]	Ready to use libftprintf.a" $(RESET)
	@$(CC) $(CFLAGS) $(COMP_FLAGS_CLUSTER) -o $(NAME) $(OBJ) -L$(LIB_DIR) -lftprintf
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
