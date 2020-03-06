/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:01:02 by hberger           #+#    #+#             */
/*   Updated: 2020/03/06 21:25:50 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void				lstclear(t_envar *lst)
{
	t_envar			*current;
	t_envar			*next;

	if (lst == 0)
		return ;
	current = lst;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	lst = NULL;
}

static void			free_redirections(t_commands_list *list, int i)
{
	t_strlist		*tmp;

	while (list->command[i].in)
	{
		free(list->command[i].in->str);
		tmp = list->command[i].in;
		list->command[i].in = list->command[i].in->next;
		free(tmp);
	}
	while (list->command[i].out)
	{
		free(list->command[i].out->str);
		tmp = list->command[i].out;
		list->command[i].out = list->command[i].out->next;
		free(tmp);
	}
}

void				commands_lstclear(t_commands_list *list)
{
	t_commands_list	*tmp;
	int				i;
	int				j;

	while (list)
	{
		i = 0;
		while (list->command[i].args)
		{
			free_redirections(list, i);
			j = 0;
			while (list->command[i].args[j])
			{
				free(list->command[i].args[j]);
				j++;
			}
			free(list->command[i].args);
			i++;
		}
		free(list->command);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}
