/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:01:02 by hberger           #+#    #+#             */
/*   Updated: 2020/02/20 20:45:54 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void		lstclear(t_envar *lst)
{
	t_envar	*current;
	t_envar	*next;

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
