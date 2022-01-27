# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 12:11:44 by ldurante          #+#    #+#              #
#    Updated: 2022/01/27 17:22:20 by ldurante         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VARIABLE DECLARATIONS #

NAME = minishell
CC = gcc
RM = rm -f
MAKE = make
READLINE = -L ~/.brew/opt/readline/lib -lreadline
CFLAGS = -Wall -Werror -Wextra -I ~/.brew/opt/readline/include -g3
DEBUG = -g3 -fsanitize=address

# COLORS #

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
GREY = \033[2;37m
MAGENTA = \033[0;35m
CURSIVE = \033[3m
NO_COLOR = \033[0m

# SOURCES & OBJECTS #

SRCS =	srcs/main.c \
		srcs/error_msg.c \
		srcs/read_input.c \
		srcs/signal.c \
		srcs/redirections.c \
		srcs/builtins/cd.c \
		srcs/builtins/pwd.c \
		srcs/builtins/echo.c \
		srcs/builtins/env.c \
		srcs/builtins/env_list.c \
		srcs/builtins/export.c \
		srcs/builtins/unset.c \
		srcs/builtins/exit.c \
		srcs/executer/exec_args.c \
		srcs/executer/exec_cmd.c \
		srcs/executer/pipes.c \
		srcs/executer/args_list.c \
		srcs/executer/here_doc.c \
		srcs/lexer/check_args.c \
		srcs/lexer/expand.c \
		srcs/lexer/expand_aux.c \
		srcs/lexer/quotes.c \
		srcs/lexer/split_args.c \
		srcs/lexer/token.c \
		srcs/lexer/check_error_pipes.c \

OBJS = $(SRCS:.c=.o)

# RULES #

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -s all -C libft
	@$(CC) $(CFLAGS) $(OBJS) libft/libft.a $(READLINE) -o $(NAME)
	@echo "$(GREY) Minishell compiled $(GREEN) ✔✔✔ $(NO_COLOR)"

clean:
	@clear
	@$(RM) $(OBJS)
	@$(MAKE) clean -C libft
	@echo "$(RED) **** Object files removed **** $(NO_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) libft/libft.a
	@echo "$(RED) **** Fclean done **** $(NO_COLOR)"

re: fclean all

.PHONY: all re clean fclean test

.SILENT: $(OBJS)