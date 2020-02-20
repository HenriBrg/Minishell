/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:10:59 by hberger           #+#    #+#             */
/*   Updated: 2020/02/20 01:52:01 by macasubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#include <stdio.h>



int				parse(char *input)
{
	char		*separators1[] = {"|", NULL};
	//char		*separators2[] = {"<", ">", ">>", NULL};
	t_strlist	*pipe_list;

	// avant : verifier le format de la ligne
	pipe_list = ft_supersplit(input, separators1, 1, "");

	while (pipe_list)
	{
		printf("%s\n", pipe_list->str);
		pipe_list = pipe_list->next;
	}

	/*int	i = 0;
	while (pipes[i])
	{
		printf("%s\n", pipes[i]);
		i++;
	}*/
	return (0);
}
