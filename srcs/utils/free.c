/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:01:02 by hberger           #+#    #+#             */
/*   Updated: 2020/02/19 17:08:58 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void		lstclear(t_list *lst)
{
	t_list	*current;
	t_list	*next;

	if (lst == 0)
		return ;
	current = lst;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	lst = NULL;
}
