/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 23:52:46 by hberger           #+#    #+#             */
/*   Updated: 2020/02/21 00:58:39 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** exit() peut prendre un argument qui donnera la valeur d'exit
** Faut-il gerer les leaks sur un exit ?
*/

void	builtinexit(char **cmds)
{
	int	ret;

	ft_putstr("exit\n");
	if (cmds == 0)
		exit(EXIT_SUCCESS);
	if (ft_strslen(cmds) == 1)
		exit(EXIT_SUCCESS);
	if (ft_strslen(cmds) == 2 && ft_isdigit(cmds[1][0]) == 0)
	{
		ft_putstr("exit: \n");
		ft_putstr(cmds[1]);
		ft_putstr(": numeric argument required\n");
		exit(EXIT_FAILURE);
	}
	ret = ft_atoi(cmds[1]);
	if (ft_strslen(cmds) > 2)
	{
		ft_putstr("exit\n");
		ft_putstr("exit: too many arguments\n");
		exit(EXIT_FAILURE);
	}
	// exit(EXIT_FAILURE);
	// Est-ce qu'on exit quand meme si trop d'argument ?
	// Est ce qu'un exit peut fail ?
}
