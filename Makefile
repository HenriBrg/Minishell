# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hberger <hberger@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/18 19:03:18 by hberger           #+#    #+#              #
#    Updated: 2020/02/18 20:22:42 by hberger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Wextra -Werror

SRCS = srcs/main.c

OBJS = ${SRCS:.c=.o}

HEADER = -I ./inc/

ifndef VERBOSE
.SILENT:
endif

all: $(NAME)

.c.o:
	gcc $(FLAGS) $(HEADER) -c $< -o $@

$(NAME): $(OBJS)
	make -C libft

	gcc $(FLAGS) $(SRCS) -o $(NAME) -L. libft/libft.a

clean:
	make clean -C libft
	rm -f srcs/*.o

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
