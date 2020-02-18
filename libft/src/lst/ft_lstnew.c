/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:35:22 by hberger           #+#    #+#             */
/*   Updated: 2019/10/16 18:16:22 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list	*current;

	if (!(current = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	current->content = content;
	current->next = NULL;
	return (current);
}
