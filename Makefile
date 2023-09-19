# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiyunlee <jiyunlee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/30 20:04:18 by jiyunlee          #+#    #+#              #
#    Updated: 2023/09/19 18:43:09 by jiyunlee         ###   ########.fr        #
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

PARSE_DIR	= ./parsing/
SRCS_PARSE	= env_init.c \
			  shell_init.c \
			  cmd_init.c \
			  parse_by_pipe.c \
			  parse_by_redir.c \
			  parse_by_space.c \
			  delete_invalid_token.c \
			  handle_syntax_error.c \
			  replace_env.c \
			  t_env_func.c \
			  t_token_func.c \
			  t_str_func.c \
			  t_redir_func.c
OBJS_PARSE	= $(addprefix $(PARSE_DIR), $(SRCS_PARSE:.c=.o))

EXEC_DIR	= ./execute/
SRCS_EXEC	= execute.c \
			  re_init_shell_info.c \
			  remove_quotation.c \
			  init_exec_info.c \
			  multi_process.c \
			  set_redir.c \
			  exec_command.c \
			  unlink_here_doc.c \
			  error_exit.c
OBJS_EXEC	= $(addprefix $(EXEC_DIR), $(SRCS_EXEC:.c=.o))

BUILT_DIR	= ./builtin/
SRCS_BUILT	=
OBJS_BUILT	= $(addprefix $(BUILT_DIR), $(SRCS_BUILT:.c=.o))

UTILS_DIR	= ./utils/
SRCS_UTILS	= set_signal.c \
			  free_all.c
OBJS_UTILS	= $(addprefix $(UTILS_DIR), $(SRCS_UTILS:.c=.o))


SRCS		= minishell.c $(SRCS_PARSE) $(SRCS_EXEC) $(SRCS_BUILT) $(SRCS_UTILS)
OBJS		= minishell.o $(OBJS_PARSE) $(OBJS_EXEC) $(OBJS_BUILT) $(OBJS_UTILS)

all		: $(NAME)

%.o		: %.c
	@$(CC) $(CFLAGS) $(OBJS_FLAGS) -c $< -o $@

$(NAME)	: $(OBJS)
	@$(MAKE) -C $(LIB_DIR)
	@$(CC) $(CFLAGS) $(COMP_FLAGS) -o $(NAME) $(OBJS) -L$(LIB_DIR) -lftprintf
	@echo $(GREEN) "⚡︎	[ minishell ]	Ready to use minishell" $(RESET)

clean	:
	@$(MAKE) -C $(LIB_DIR) clean
	@echo $(YELLOW) "✭	[ libftprintf ]	Removed Object files" $(RESET)
	@$(RM) $(OBJS) $(OBJS_PARSE) $(OBJS_EXEC)
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
