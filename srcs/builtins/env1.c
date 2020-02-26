/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 15:48:11 by hberger           #+#    #+#             */
/*   Updated: 2020/02/26 20:17:24 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** Voir dans env2.c
** Verifie que l'argument ne commence pas par un =
** Si ok, on extrait le name et l'eventuelle value qui peut etre nulle (var=)
** puis on pushbackenvar()
*/

void		exportenvar(char **cmds, t_envar *envar)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (cmds[++i])
	{
		if (cmds[i][0] == '=')
		{
			ft_putstr("minishell: export: `");
			ft_putstr(cmds[i]);
			ft_putstr("': not a valid identifier\n");
			g_exitvalue = EXIT_FAILURE;
			return ;
		}
		else if (cmds[i][0])
		{
			namevaluefilter(cmds[i], &name, &value);
			if (name)
				pushbackenvar(name, value, envar);
			sortenvar(envar);
		}
	}
	g_exitvalue = EXIT_SUCCESS;
}

/*
** Affiche chaque variable d'environnement
*/

void		printenv(t_envar *envar)
{
	t_envar	*current;

	current = envar;
	while (current)
	{
		if (ft_strlen(current->value) > 0)
		{
			write(1, current->name, ft_strlen(current->name));
			write(1, "=", 1);
			write(1, current->value, ft_strlen(current->value));
			write(1, "\n", 1);
		}
		current = current->next;
	}
	g_exitvalue = EXIT_SUCCESS;
}

/*
** Quasiment identique à un lst remove if ()
*/

void		removevar(char *name, t_envar *envar)
{
	t_envar *next;
	t_envar *current;
	t_envar *previous;

	current = envar;
	previous = envar;
	while (current)
	{
		next = current->next;
		if (ft_strcmp(current->name, name) == 0)
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

void		unsetenvar(char **cmds, t_envar *envar)
{
	int		i;

	i = 1;
	while (cmds[i])
	{
		if (ft_strchr(cmds[i], '='))
		{
			ft_putstr("minishell: unset: `");
			ft_putstr(cmds[i]);
			ft_putstr("': not a valid identifier\n");
			g_exitvalue = EXIT_FAILURE;
		}
		else
		{
			removevar(cmds[i], envar);
			g_exitvalue = EXIT_SUCCESS;
		}
		i++;
	}
}

/*
** Rajouter le case insensitive
*/

void		builtinsenv(char **cmds, t_envar *envar)
{
	if (strcmpcasei(cmds[0], "env"))
		printenv(envar);
	else if (strcmpcasei(cmds[0], "export")) // bloquer export avec " dans le nom
		exportenvar(cmds, envar);
	else if (strcmpcasei(cmds[0], "unset"))
		unsetenvar(cmds, envar);
}
