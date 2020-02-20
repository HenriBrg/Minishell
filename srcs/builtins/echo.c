/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:11:47 by hberger           #+#    #+#             */
/*   Updated: 2020/02/20 21:52:17 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* TODO
** ~ v9 > echo ls > tmp
** ~ v9 > sh < tmp
** Makefile	libft		srcs
** includes	minishell	tmp
*/

/*
** echo() print chaque argument séparé d'un espace
** puis un \n sauf si flag -n
** echo -n -n n'affiche rien
*/

void	builtinecho(char **cmds, t_envar *envar)
{
	int		i;
	int		nflag;
	char	*tmp;

	if (cmds[1] == 0)
		return (ft_putstr("\n"));
	i = 0;
	nflag = 1;
	while (ft_strcmp(cmds[++i], "-n") == 0)
		nflag = 0;
	while (cmds[++i])
	{
		tmp = cmds[i];
		if (cmds[i][0] == '$')
			tmp = getvar(envar, cmds[i]);
		write(1, tmp, ft_strlen(tmp));
		write(1, " ", 1);
	}
	write(1, "\n", nflag);
	// REMEMBER $?
}
