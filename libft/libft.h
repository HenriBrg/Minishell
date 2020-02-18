/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:17:16 by hberger           #+#    #+#             */
/*   Updated: 2020/02/18 21:58:47 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

typedef struct	s_list
{
	void				*content;
	struct s_list		*next;
}				t_list;

typedef struct	s_btree
{
	struct s_btree		*left;
	struct s_btree		*right;
	void				*item;
}				t_btree;

/*
** Fonctions de btree
*/

t_btree			*btree_create_node(void *item);
void			*btree_search_item(t_btree *root, void *data_ref,
	int (*cmpf)(void *, void *));
void			btree_insert_data(t_btree **root, void *item,
	int (*cmpf)(void *, void *));
void			btree_apply_suffix(t_btree *root, void (*applyf)(void *));
void			btree_apply_prefix(t_btree *root, void (*applyf)(void *));
void			btree_apply_infix(t_btree *root, void (*applyf)(void *));

/*
** Fonctions de conversion
*/

int				ft_atoi(const char *str);
double			ft_atod(const char *str);
char			*ft_itoa(int n);
char			*ft_itoa_base(char *base, int n);
char			*ft_intmaxt_toa_base(char *base, intmax_t n);
char			*ft_uintmaxt_toa_base(char *base, uintmax_t n);

/*
** Fonctions Listes Chainées
*/

void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstnew(void *content);

/*
** Fonctions Diverses
*/

void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
int				ft_isdigit(int c);
int				ft_isalpha(int c);
int				ft_isspace(int c);
int				get_next_line(int fd, char **line);

/*
** Fonctions d'affichage
*/

void			ft_putchar(char c);
void			ft_putnbr(int nb);
void			ft_putstr(const char *str);
void			ft_putendl_fd(char *s, int fd);
void			ft_putstr_fd(char *s, int fd);

/*
** Fonctions sur les strings
*/
int				ft_strslen(char **strs);
int				ft_stroccurs(char *src, char c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strchr(const char *s, int c);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strdup(const char *src);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strncat(char *dest, char *src, size_t nb);
char			*ft_strncpy(char *dst, const char *src, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strnstr(const char *str, const char *to_find, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *str, const char *to_find);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strndup(const char *src, size_t n);
char			**ft_strsplit(char *str, char *charset);
void			ft_strsfree(char **strs);
size_t			ft_strlen(const char *str);

#endif
