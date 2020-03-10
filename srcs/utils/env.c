/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:55:15 by hberger           #+#    #+#             */
/*   Updated: 2020/03/10 21:27:03 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int			charequalci(char c1, char c2)
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
		while (s1[i] && charequalci(s1[i], s2[i]))
			i++;
		return (charequalci(s1[i], s2[i]) ? 1 : 0);
	}
	return (0);
}

/*
** Créer un nouveau maillon depuis le string d'env em coupant au '='
** Ajouter la creation incluant le $
** +1 car on saute le '='
*/

t_envar		*lstnewenvar(char *envstr)
{
	int		i;
	t_envar	*current;

	if (!(current = (t_envar*)malloc(sizeof(t_envar))))
		return (NULL);
	i = ft_strrchr(envstr, '=') - envstr;
	current->name = ft_strndup(envstr, i);
	current->value = ft_strdup(envstr + i + 1);
	current->assigned = 1;
	current->next = NULL;
	return (current);
}

/*
** getvar() retourne la valeur de la variable d'environnement demandée
** en renvoyant un pointeur sur la valeur de la variable
*/

char		*getvar(t_envar *envar, char *name)
{
	t_envar	*current;

	current = envar;
	while (current != 0)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (0);
}

/*
** Convertit le tableau **env en liste chainées
*/

t_envar		*lstenv(char **env)
{
	int			i;
	t_envar		*begin;
	t_envar		*current;
	t_envar		*previous;

	i = -1;
	begin = 0;
	while (env[++i] != 0)
	{
		current = lstnewenvar(env[i]);
		if (begin != 0)
			previous->next = current;
		else
			begin = current;
		previous = current;
	}
	return (begin);
}
