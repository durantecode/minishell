# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 12:11:44 by ldurante          #+#    #+#              #
#    Updated: 2021/11/09 13:18:17 by dpavon-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VARIABLE DECLARATIONS #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
MAKE = make
DEBUG = -g3 -fsanitize=address
READLINE = -lreadline
# COLORS #

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
GREY = \033[2;37m
MAGENTA = \033[0;35m
CURSIVE = \033[3m
NO_COLOR = \033[0m

# SOURCES & OBJECTS #

SRCS = srcs/main.c srcs/builtins.c

OBJS = $(SRCS:.c=.o)

# RULES #

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -s all -C libft
	@$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME) $(READLINE)
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