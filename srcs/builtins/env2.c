/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:57:36 by hberger           #+#    #+#             */
/*   Updated: 2020/05/02 15:27:25 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	t_envar	*backup;
	t_envar	*envarcopy;

	envarcopy = fullcopyenvar(envar);
	sortenvar(envarcopy);
	backup = envarcopy;
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
	lstclear(backup);
}

/*
** On change la valeur si la variable existe deja
** Autrement, on malloc puis on la positionne en fin de liste
*/

void		pushnorminette(t_envar **new, char *name, char *value)
{
	(*new)->name = name;
	(*new)->value = value;
	(*new)->next = NULL;
}

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
			current->assigned = (value ? 1 : 0);
			free(name);
			return (free(value));
		}
		current = current->next;
	}
	if (!(new = (t_envar *)malloc(sizeof(t_envar))))
		return ;
	pushnorminette(&new, name, value);
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
