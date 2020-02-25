# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hberger <hberger@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/18 19:03:18 by hberger           #+#    #+#              #
#    Updated: 2020/02/25 19:21:04 by hberger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Wextra -Werror

SRCS = srcs/main.c srcs/utils/env.c srcs/utils/free.c 				    	   \
	   srcs/parser/parse.c srcs/parser/ft_supersplit.c srcs/utils/errors.c     \
	   srcs/builtins/cd.c srcs/builtins/echo.c srcs/builtins/env1.c			   \
	   srcs/builtins/env2.c srcs/builtins/pwd.c srcs/builtins/exit.c		   \
	   srcs/executables/exec.c srcs/utils/signals.c srcs/direction/pipes.c

OBJS = ${SRCS:.c=.o}

HEADER = -I ./inc/

# ifndef VERBOSE
# .SILENT:
# endif

all: $(NAME)

.c.o:
	gcc $(FLAGS) $(HEADER) -c $< -o $@

$(NAME): $(OBJS)
	make -C libft
	gcc $(FLAGS) $(SRCS) -o $(NAME) -L. libft/libft.a

run: $(NAME)
	./minishell

clean:
	make clean -C libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
