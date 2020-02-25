/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:55:23 by hberger           #+#    #+#             */
/*   Updated: 2020/02/25 19:41:44 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char		*replacedollars(char **cmds, t_envar *envar)
{
	(void)cmds;
	(void)envar;
	// penser aussi a $? (globale)
	return 0;
}

/*
** Affiche le prompteur
*/

void		prompt(t_envar *envar)
{
	(void)envar;
	ft_putstr(getvar(envar, "PWD"));
	ft_putstr("/ ------> ");
}

/*
**
*/

int			main(int ac, char **av, char **env)
{
	char	*input;
	t_envar	*envar;

	char	**cmds;

	(void)av;
	envar = NULL;
	input = NULL;
	if (ac != 1 || (envar = lstenv(env)) == 0)
		return (-1);
	siglisten();
	while (42)
	{
		prompt(envar);
		g_shellisrunning = 0;
		get_next_line(0, &input);

		//if ((parse(input)) == -1)
		//	return (-1);

		if (ft_strlen(input) != 0)
		{
			cmds = ft_strsplit(input, " ");
			g_shellisrunning = 1;
			if (isbuiltin(cmds))
				executebuiltins(cmds, envar);
			else
				executables(cmds, envar);
			ft_strsfree(cmds);
		}
		free(input);
	}
	lstclear(envar);
	return (0);
}
