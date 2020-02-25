/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 23:52:46 by hberger           #+#    #+#             */
/*   Updated: 2020/02/25 18:54:22 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** Retourne 1 si le string n'est composé QUE de chiffre
*/

int		strisdigit(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		if (ft_isdigit(cmd[i]) == 0)
			return (0);
	return (1);
}

/*
** exit() peut prendre un argument qui donnera la valeur d'exit
** 2nd if() --> exit(255) comme dans bash si argument non numerique
** Si ret > 255, la valeur d'exit = modulo 256
** https://unix.stackexchange.com/questions/418784/what-is-the-min-and-
** max-values-of-exit-codes-in-linux
*/

void	builtinexit(char **cmds)
{
	int	ret;

	ft_putstr("exit\n");
	if (ft_strslen(cmds) == 1)
		exit((g_exitvalue = EXIT_SUCCESS));
	if (ft_strslen(cmds) >= 2 &&
	(strisdigit(cmds[1]) == 0 && cmds[1][0] != '-'))
	{
		ft_putstr(cmds[1]);
		ft_putstr(": numeric argument required\n");
		g_exitvalue = 255;
		exit(255);
	}
	ret = ft_atoi(cmds[1]);
	if (ft_strslen(cmds) >= 3)
	{
		ft_putstr("exit: too many arguments\n");
		g_exitvalue = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	if (ret > 255)
		ret = ret % 256;
	g_exitvalue = ret;
	exit(ret);
}
