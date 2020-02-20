/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:06:53 by hberger           #+#    #+#             */
/*   Updated: 2020/02/20 18:38:21 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdio.h>

# define PATH_MAX 4096

typedef struct		s_lstcmds
{
	int				position;
	char			*from;
	char			*out;
	char			**tabs;

	struct s_env	*next;
}					t_lstcmds;


typedef struct		s_envar
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_envar;

// extern int exitvalue = 0;

/*
** utils/
*/

char		*getvar(t_list *envar, char *name);
t_list		*lstenv(char **env);
void		lstclear(t_list *lst);
int			inputcontrol(char *input);
int			strcmpcasei(char *s1, char *s2);

/*
** parse/
*/

int			parse(char *input);

#endif
