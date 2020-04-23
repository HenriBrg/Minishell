NAME = libft.a

SRCS =  src/str/ft_strcmp.c  src/str/ft_strncmp.c src/str/ft_strcat.c		   \
		src/str/ft_strchr.c  src/str/ft_strcpy.c  src/str/ft_strdup.c		   \
		src/str/ft_strjoin.c src/str/ft_strncat.c src/str/ft_strncpy.c		   \
		src/str/ft_strnew.c  src/str/ft_strnstr.c src/str/ft_strrchr.c		   \
		src/str/ft_strstr.c  src/str/ft_strsub.c  src/str/ft_strlen.c		   \
		src/str/ft_strndup.c src/str/ft_stroccurs.c	src/str/ft_strsplit.c	   \
		src/str/ft_strsfree.c src/str/ft_strslen.c src/str/ft_strlcpy.c		   \
		src/str/ft_strtrim.c \
		src/others/ft_bzero.c src/others/ft_calloc.c src/others/ft_memset.c    \
		src/others/ft_memcpy.c src/others/ft_isdigit.c src/others/ft_isalpha.c \
		src/others/ft_isspace.c	src/others/get_next_line.c					   \
																			   \
		src/print/ft_putnbr.c src/print/ft_putstr.c	src/print/ft_putchar.c	   \
		src/print/ft_putstr_fd.c src/print/ft_putendl_fd.c					   \
																			   \
		src/lst/ft_lstadd_back.c src/lst/ft_lstadd_front.c 					   \
		src/lst/ft_lstsize.c     src/lst/ft_lstnew.c						   \
																			   \
		src/conversion/ft_atoi.c src/conversion/ft_itoa.c					   \
		src/conversion/ft_itoa_base.c src/conversion/ft_intmaxt_toa_base.c	   \
		src/conversion/ft_uintmaxt_toa_base.c src/conversion/ft_atod.c		   \
																			   \
		src/btree/btree_apply_infix.c  src/btree/btree_apply_suffix.c		   \
		src/btree/btree_insert_data.c src/btree/btree_apply_prefix.c		   \
		src/btree/btree_create_node.c  src/btree/btree_search_item.c

OBJS = ${SRCS:.c=.o}

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

.c.o:
	clang $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
