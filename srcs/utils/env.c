/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:55:15 by hberger           #+#    #+#             */
/*   Updated: 2020/02/19 17:12:12 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** getvar() retourne la valeur de la variable d'environnement demandée
** en renvoyant un pointeur sur la valeur de la variable, donc on saute
** la taille de son nom et le '=', avec return (env[i] + ft_strlen(name) + 1);
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
