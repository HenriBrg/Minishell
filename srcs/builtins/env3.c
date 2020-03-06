/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:52:08 by hberger           #+#    #+#             */
/*   Updated: 2020/03/06 19:07:47 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void			swapenvar(t_envar *current, t_envar *next)
{
	int			tmpassigned;
	char		*tmpname;
	char		*tmpvalue;

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

static t_envar	*copylstnewvar(t_envar *envar)
{
	t_envar		*current;

	if (!(current = (t_envar*)malloc(sizeof(t_envar))))
		return (NULL);
	current->name = ft_strdup(envar->name);
	current->value = (envar->value) ? ft_strdup(envar->value) : 0;
	current->assigned = envar->assigned;
	current->next = NULL;
	return (current);
}

t_envar			*fullcopyenvar(t_envar *origin)
{
	t_envar		*begin;
	t_envar		*current;
	t_envar		*previous;

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
