/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:11:47 by hberger           #+#    #+#             */
/*   Updated: 2020/02/21 16:23:23 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** echo() print chaque argument toujours séparés d'un espace
** puis un \n sauf si flag -n
** echo -n -n n'affiche rien
** TODO : gerer les $VAR a moins qu'on le gere avant dans l'input (impossible d'escape de $ dans bash)
*/

void		builtinecho(char **cmds, t_envar *envar)
{
	int		i;
	int		nflag;
	char	*tmp;

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
		tmp = cmds[i];
		if (cmds[i][0] == '$')
			tmp = getvar(envar, cmds[i] + 1); // On saute le $
		write(1, tmp, ft_strlen(tmp));
		if (cmds[i + 1])
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", nflag);
	// REMEMBER $?
}
