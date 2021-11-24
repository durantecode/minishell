# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 12:11:44 by ldurante          #+#    #+#              #
#    Updated: 2021/11/24 12:03:33 by ldurante         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VARIABLE DECLARATIONS #

NAME = minishell
CC = gcc
RM = rm -f
MAKE = make
READLINE = -L ~/.brew/opt/readline/lib -lreadline
CFLAGS = -Wall -Werror -Wextra -I ~/.brew/opt/readline/include
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
		srcs/read_input.c \
		srcs/builtins.c \
		srcs/echo.c \
		srcs/env.c \
		srcs/export.c \
		srcs/unset.c \
		srcs/signal.c \
		srcs/exec_cmd.c \
		srcs/check_args.c \
		srcs/quotes.c \
		srcs/expand.c \

OBJS = $(SRCS:.c=.o)

# RULES #

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -s all -C libft
	@$(CC) $(CFLAGS) $(OBJS) libft/libft.a $(READLINE) -o $(NAME)
	@echo "$(GREY) Minishell compiled $(GREEN) ✔✔✔ $(NO_COLOR)"

test: all
	@echo "$(YELLOW) **** Running test Minishell **** $(NO_COLOR)"
	./minishell

normi:
	norminette -R CheckForbiddenSourceHeaders srcs/*.c srcs_utils/*.c includes/*.h

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