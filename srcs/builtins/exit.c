/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 23:52:46 by hberger           #+#    #+#             */
/*   Updated: 2020/03/10 21:32:37 by hberger          ###   ########.fr       */
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
** ➜  minishell git:(hb) ✗ bash
** bash-3.2$ exit 2> file
** ➜  minishell git:(hb) ✗ cat file
** exit
** ➜  minishell git:(hb) ✗ echo -n > file
** ➜  minishell git:(hb) ✗ bash
** bash-3.2$ exit 1> file
** exit
** ➜  minishell git:(hb) ✗ cat file
** ➜  minishell git:(hb) ✗
*/

void	builtinexit(char **cmds, int piped)
{
	unsigned char	ret;

	if (piped == 0)
		ft_putstr_fd("exit\n", 2);
	if (ft_strslen(cmds) == 1)
		exit(g_exitvalue);
	if (ft_strslen(cmds) >= 2 && (strisdigit(cmds[1]) == 0
				&& (cmds[1][0] != '-' || !ft_isdigit(cmds[1][1]))))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmds[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit((g_exitvalue = 2));
	}
	ret = (unsigned char)ft_atoi(cmds[1]);
	if (ft_strslen(cmds) >= 3)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_exitvalue = 2;
		return ;
	}
	g_exitvalue = (int)ret;
	exit(g_exitvalue);
}
