/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:55:15 by hberger           #+#    #+#             */
/*   Updated: 2020/02/20 17:09:45 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		ft_letterequci(char c1, char c2)
{
	if (c1 == c2)
		return (1);
	else if (c1 >= 'a' && c1 <= 'z')
	{
		if (c2 >= 'a' && c2 <= 'z')
			return (c1 == c2);
		else
			return (c1 - 32 == c2);
	}
	else
	{
		if (c2 >= 'A' && c2 <= 'Z')
			return (c1 == c2);
		else
			return (c1 == c2 - 32);
	}
}

int			strcmpcasei(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i] && ft_letterequci(s1[i], s2[i]))
			i++;
		return (ft_letterequci(s1[i], s2[i]) ? 1 : 0);
	}
	return (0);
}


/*
** getvar() retourne la valeur de la variable d'environnement demandée
** en renvoyant un pointeur sur la valeur de la variable, donc on saute
** la taille de son nom et le '=', avec return (env[i] + ft_strlen(name) + 1);
**
** TODO : trim(name, "$()\"")
*/

char		*getvar(t_list *envar, char *name)
{
  t_list	*current;

  current = envar;
  while (current != 0)
  {
    if (ft_strncmp(current->content, name, ft_strlen(name) - 1) == 0)
      return (current->content + ft_strlen(name) + 1);
    current = current->next;
  }
  return (0);
}

/*
** Convertit le tableau **env en liste chainées
*/

t_list		*lstenv(char **env)
{
	int			i;
	t_list		*begin;
	t_list		*current;
	t_list		*previous;

	if (env == 0 || *env == 0)
		return (0);
	i = -1;
	begin = 0;
	while (env[++i] != 0)
	{
		current = ft_lstnew(env[i]);
		if (begin != 0)
			previous->next = current;
		else
			begin = current;
		previous = current;
		// printf("%s\n", (char*)(current->content));
	}
	return (begin);
}
