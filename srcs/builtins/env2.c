/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:57:36 by hberger           #+#    #+#             */
/*   Updated: 2020/03/05 23:23:22 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void		swapenvar(t_envar *current, t_envar *next)
{
	int 	tmpassigned;
	char	*tmpname;
	char	*tmpvalue;

	tmpname = current->name;
	tmpvalue = current->value;
	tmpassigned = current->assigned;
	current->name = next->name;
	current->value = next->value;
	current->assigned = next->assigned;
	next->name = tmpname;
	next->value = tmpvalue;
	next->assigned = tmpassigned;

}

t_envar		*copylstnewvar(t_envar *envar)
{
	t_envar	*current;

	if (!(current = (t_envar*)malloc(sizeof(t_envar))))
		return (NULL);
	current->name = ft_strdup(envar->name);
	current->value = (envar->value) ? ft_strdup(envar->value) : 0;
	current->assigned = envar->assigned;
	current->next = NULL;
	return (current);
}

t_envar		*fullcopyenvar(t_envar *origin)
{
	t_envar		*begin;
	t_envar		*current;
	t_envar		*previous;

	current = origin;
	begin = 0;
	while (origin != 0)
	{
		current = copylstnewvar(origin);
		if (begin != 0)
			previous->next = current;
		else
			begin = current;
		previous = current;
		origin = origin->next;
	}
	return (begin);
}


void		sortenvar(t_envar *envarcopy)
{
	t_envar	*current1;
	t_envar	*current2;

	current1 = envarcopy;
	while (current1)
	{
		current2 = envarcopy;
		while (current2)
		{
			if (current2->next && ft_strcmp(current2->name,
				current2->next->name) > 0)
				swapenvar(current2, current2->next);
			current2 = current2->next;
		}
		current1 = current1->next;
	}
}

void		printdeclaredvars(t_envar *envar)
{
	t_envar	*envarcopy;

	envarcopy = fullcopyenvar(envar);
	sortenvar(envarcopy);
	while (envarcopy)
	{
		write(1, "declare -x ", 11);
		write(1, envarcopy->name, ft_strlen(envarcopy->name));
		if (envarcopy->value)
		{
			write(1, "=\"", 2);
			write(1, envarcopy->value, ft_strlen(envarcopy->value));
			write(1, "\"\n", 2);
		}
		else
			write(1, "\n", 1);
		envarcopy = envarcopy->next;
	}
	lstclear(envarcopy);
}

/*
** On change la valeur si la variable existe deja
** Autrement, on malloc puis on la positionne en fin de liste
*/

void		pushbackenvar(char *name, char *value, t_envar *envar, int assigned)
{
	t_envar	*new;
	t_envar	*current;

	current = envar;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = (value ? ft_strdup(value) : 0);
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
	new->assigned = assigned;
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
	i = (tmp) ? tmp - cmd : ft_strlen(cmd);
	*name = ft_strndup(cmd, i);
	if (tmp)
		*value = ft_strdup(cmd + ft_strlen(*name) + 1);
	else
		*value = 0;
}
