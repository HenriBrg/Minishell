/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:11:47 by hberger           #+#    #+#             */
/*   Updated: 2020/05/02 16:30:13 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char		*finishgetdest(t_envar *envar, char *varname, int specific)
{
	if (getvar(envar, varname) == 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(varname, 2);
		ft_putendl_fd(" not set", 2);
		g_exitvalue = EXIT_FAILURE;
		return (NULL);
	}
	if (specific == 1)
		ft_putendl_fd(getvar(envar, varname), 1);
	return (ft_strdup(getvar(envar, varname)));
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
		ft_putstr(cmds[i]);
		if (cmds[i + 1])
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", nflag);
	g_exitvalue = EXIT_SUCCESS;
}
