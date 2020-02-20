/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:06:53 by hberger           #+#    #+#             */
/*   Updated: 2020/02/20 03:17:59 by macasubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdio.h>


/*
** utils/
*/

typedef struct			s_strlist
{
	char				*str;
	struct s_strlist	*next;
}						t_strlist;

typedef struct			s_command
{
	char				*command;
	int					stdout_type;
	char				*out;
	char				*in;
}						t_command;

typedef struct			s_envsplit
{
	char				*string;
	char				**separators;
	int					inclusion;
	char				*trim;
	int					index;
	char				quotes[3];
	t_strlist			*list;
}						t_envsplit;

char					*getvar(t_list *envar, char *name);
t_list					*lstenv(char **env);
void					lstclear(t_list *lst);
int						inputcontrol(char *input);
void					handle_error(char *message);

/*
** parse/
*/

int						parse(char *input);
t_strlist				*ft_supersplit(char *string, char **separators,
										int inclusion, char *trim);

#endif
