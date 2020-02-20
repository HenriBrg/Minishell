/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 15:48:11 by hberger           #+#    #+#             */
/*   Updated: 2020/02/20 17:48:59 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** On change la valeur si la variable existe deja
** Autrement, on malloc puis on la positionne en fin de liste
*/

void		pushbackenvar(char *name, char *value, t_list *envar)
{
	t_envar	*new;
	t_envar	*current;

	current = envar;
	while (current)
	{
		if (ft_strcmp(current->name, name))
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
** Retourne name et value rempli correctement
*/

void		namevaluefilter(char *cmd, char **name, char **value)
{
	size_t		i;
	char		*tmp;

	tmp = ft_strrchr(cmd, '=');
	i = (tmp) ? cmd - tmp : ft_strlen(cmd);
	name = ft_strndup(cmd, i);
	if (tmp)
		*value = ft_strdup(cmd + ft_strlen(name) + 1);
	else
		*value = 0;
}

void	pushenv(char **cmds, t_list *envar)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (cmds[++i])
	{
		if (cmds[i][0] == '=')
		{
			ft_putstr("minishell: export: `", cmds[i]);
			ft_putstr(cmds[i]);
			ft_putstr("': not a valid identifier\n");
			// REMEMBER $?
			return ;
		}
		else if (cmds[i][0])
		{
			namevaluefilter(cmds[i], &name, &value);
			if (name)
				push_back_var(name, value);
		}
	}
	// Erreur d'export ?
	// REMEMBER $?
}

/*
** Affiche chaque variable d'environnement
*/

void		printenv(t_list *envar)
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
	// REMEMBER $?
}

/*
** Quasiment identique à un lst remove if ()
*/

void		removevar(char *name, t_list *envar)
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

void		popenv(char **cmds, t_list *envar)
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
			removevar(cmds[i], envar);
			// REMEMBER $?
	}
}

/*
** Rajouter le case insensitive
*/

void	builtinsenv(char **cmds, t_list *envar)
{
	if (strcmpcasei(cmds[0], "env"))
		printenv();
	else if (strcmpcasei(cmds[0], "export"))
		pushenv(cmds);
	else if (strcmpcasei(cmds[0], "unset"))
		popenv(cmds);
}
