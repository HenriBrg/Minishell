/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:55:23 by hberger           #+#    #+#             */
/*   Updated: 2020/02/20 21:44:43 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
** Ajouter le path ...
*/

void		prompt(t_envar *envar)
{
	(void)envar;
	ft_putstr("------> ");
}

int			main(int ac, char **av, char **env)
{
	char	*input;
	t_envar	*envar;

	(void)ac;
	(void)av;
	if (ac != 1 || (envar = lstenv(env)) == 0)
		return (-1);
	//listen();
	while (42)
	{
		prompt(envar);
		get_next_line(0, &input);
		if ((parse(input)) == -1)
			return (-1);
		free(input);
		// execute ();
	}
	lstclear(envar);
	return (0);
}
