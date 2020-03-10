/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:11:47 by hberger           #+#    #+#             */
/*   Updated: 2020/03/10 20:41:07 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** echo() print chaque argument toujours séparés d'un espace
** puis un \n sauf si flag -n
** echo -n -n ..... n'affiche rien
*/

void		printecho(char *str)
{
	int		c;
	char	*tmp;

	c = 0;
	tmp = ft_strtrim(str, " ");
	while (tmp[c] != 0)
	{
		if (tmp[c] == ' ')
		{
			while (tmp[c] != 0 && tmp[c] == ' ')
				c++;
			write(1, " ", 1);
		}
		write(1, &(tmp[c]), 1);
		c++;
	}
	free(tmp);
}

void		builtinecho(char **cmds, t_envar *envar)
{
	int		i;
	int		nflag;

	(void)envar;
	if (cmds[1] == 0)
		return (ft_putstr("\n"));
	i = 1;
	nflag = 1;
	while (cmds[i] && ft_strcmp(cmds[i], "-n") == 0)
	{
		nflag = 0;
		i++;
	}
	while (cmds[i])
	{
		printecho(cmds[i]);
		if (cmds[i + 1])
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", nflag);
	g_exitvalue = EXIT_SUCCESS;
}
