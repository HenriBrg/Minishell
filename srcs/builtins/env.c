/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 15:48:11 by hberger           #+#    #+#             */
/*   Updated: 2020/02/20 16:26:12 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** Quasiment identique à un lst remove if ()
*/

void		unsetvar(char *name, t_list *envar)
{
	t_list *next;
	t_list *current;
	t_list *previous;

	current = envar;
	previous = envar;
	while (current)
	{
		next = current->next;
		if (ft_strcmp(current->name, arg) ||
		(*name == '$' && ft_strcmp(current->name, name + 1)))
		{
			envar = (current == envar) ? next : envar;
			previous->next = next;
			free(current->name);
			free(current->value);
			free(current);
		}
		previous = current;
		current = current->next;
	}
}

/*
** On start à cmds[1] pour jump le 1er argument
*/

void		handleunset(char **cmds, t_list *envar)
{
	int		i;

	i = 0;
	while (cmds[++i])
	{
		if (ft_strchr(cmds[i], '='))
		{
			ft_putstr("minishell: unset: `", cmds[i]);
			ft_putstr(cmds[i]);
			ft_putstr("': not a valid identifier\n");
			// REMEMBER $?
		}
		else
			unsetvar(cmds[i], envar); // REMEMBER $?
	}
}

/*
** Rajouter le case insensitive
*/

void	builtinsenv(char **cmds, t_list *envar)
{
	if (ft_strcmp(cmds[0], "env"))
		handleenv();
	else if (ft_strcmp(cmds[0], "export"))
		handleexport(cmds);
	else if (ft_strcmp(cmds[0], "unset"))
		handleunset(cmds);
}
