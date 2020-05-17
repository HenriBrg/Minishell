/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 15:48:11 by hberger           #+#    #+#             */
/*   Updated: 2020/05/17 16:12:46 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** Voir dans env2.c
** Verifie que l'argument ne commence pas par un =
** Si ok, on extrait le name et l'eventuel value qui peut etre nulle (var=)
** puis on pushbackenvar()
** Si i == 1 : export sans argument
*/

void			exportenvar(char **cmds, t_envar *envar)
{
	int			i;
	char		*name;
	char		*value;

	i = 0;
	while (cmds[++i])
		if (!ft_isalpha(cmds[i][0]) && substitution_end_characters(cmds[i][0]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmds[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_exitvalue = cmds[i][0] == '-' ? 2 : EXIT_FAILURE;
			return ;
		}
		else if (cmds[i][0] && ft_strcmp(cmds[i], "_"))
		{
			namevaluefilter(cmds[i], &name, &value);
			if (name)
				pushbackenvar(name, value, envar,
					(ft_strchr(cmds[i], '=') ? 1 : 0));
		}
	if (i == 1)
		printdeclaredvars(envar);
	g_exitvalue = EXIT_SUCCESS;
}

/*
** Affiche chaque variable d'environnement
*/

static void		printenv(t_envar *envar)
{
	t_envar	*current;

	current = envar;
	while (current)
	{
		if (current->assigned == 1)
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

static void		removevar(char *name, t_envar *envar)
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

static void		unsetenvar(char **cmds, t_envar *envar)
{
	int		i;

	i = 1;
	while (cmds[i])
	{
		if (!ft_isalpha(cmds[i][0]) && cmds[i][0] != '_')
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmds[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
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
** TODO : bloquer export avec " dans le nom de la var
*/

void			builtinsenv(char **cmds, t_envar *envar)
{
	if (strcmpcasei(cmds[0], "env"))
		printenv(envar);
	else if (strcmpcasei(cmds[0], "export"))
		exportenvar(cmds, envar);
	else if (strcmpcasei(cmds[0], "unset"))
		unsetenvar(cmds, envar);
}
