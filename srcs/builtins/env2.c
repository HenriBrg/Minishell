/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:57:36 by hberger           #+#    #+#             */
/*   Updated: 2020/02/21 17:19:04 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	swapenvar(t_envar *current, t_envar *next)
{
	char *tmpname;
	char *tmpvalue;

	tmpname = ft_strdup(current->name);
	free(current->name);
	current->name = ft_strdup(next->name);
	tmpvalue = ft_strdup(current->value);
	free(current->value);
	current->value = ft_strdup(next->value);
	free(next->name);
	current->next->name = ft_strdup(tmpname);
	free(tmpname);
	free(next->value);
	current->next->value = ft_strdup(tmpvalue);
	free(tmpvalue);
}

/*
** Trie par valeur ASCII les variables d'ENV (exportées aussi)
*/

void	sortenvar(t_envar *envar)
{
	t_envar	*current1;
	t_envar	*current2;

	current1 = envar;
	while (current1)
	{
		current2 = envar;
		while (current2)
		{
			if (current2->next && ft_strcmp(current2->name, current2->next->name) > 0)
				swapenvar(current2, current2->next);
			current2 = current2->next;
		}
		current1 = current1->next;
	}
}

/*
** On change la valeur si la variable existe deja
** Autrement, on malloc puis on la positionne en fin de liste
*/

void		pushbackenvar(char *name, char *value, t_envar *envar)
{
	t_envar	*new;
	t_envar	*current;

	current = envar;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			free(name);
			free(value);
			return ;
		}
		current = current->next;
	}
	if (!(new = (t_envar *)malloc(sizeof(t_envar))))
		return ;
	new->name = name;
	new->value = value;
	new->next = NULL;
	current = envar;
	while (current->next)
		current = current->next;
	current->next = new;
}

/*
** Retourne name et value remplit correctement
*/

void		namevaluefilter(char *cmd, char **name, char **value)
{
	size_t		i;
	char		*tmp;

	tmp = ft_strchr(cmd, '=');
	i = (tmp) ?  tmp - cmd : ft_strlen(cmd);
	*name = ft_strndup(cmd, i);
	if (tmp)
		*value = ft_strdup(cmd + ft_strlen(*name) + 1);
	else
		*value = 0;
}
