/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:57:36 by hberger           #+#    #+#             */
/*   Updated: 2020/02/20 17:57:46 by hberger          ###   ########.fr       */
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
** Retourne name et value remplit correctement
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
