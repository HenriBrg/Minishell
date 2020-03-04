/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 20:58:19 by hberger           #+#    #+#             */
/*   Updated: 2020/03/04 22:45:29 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** switchdir() verifie la destination puis change de dossier
*/

static int			switchdir(char **cmds, char *dest)
{
	int		i;

	(void)cmds;
	if ((i = chdir(dest)) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(cmds[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return ((g_exitvalue = EXIT_FAILURE));
	}
	else
		return ((g_exitvalue = EXIT_SUCCESS));
}

static void		move(char **cmds, char *dest, t_envar *envar)
{
	char	*currentworkdir;
	char	buf[PATH_MAX - 1];
	char	*exportation;
	char	**exportcmds;

	currentworkdir = getcwd(buf, PATH_MAX - 1);
	if (dest == 0 || switchdir(cmds, dest) == -1)
		return ;
	exportation = ft_strjoin("export OLDPWD=", currentworkdir);
	exportcmds = ft_strsplit(exportation, " ");
	exportenvar(exportcmds, envar);
	free(exportation);
	ft_strsfree(exportcmds);
	currentworkdir = getcwd(buf, PATH_MAX - 1);
	exportation = ft_strjoin("export PWD=", currentworkdir);
	exportcmds = ft_strsplit(exportation, " ");
	exportenvar(exportcmds, envar);
	free(exportation);
	ft_strsfree(exportcmds);
}

static char		*getdest(char **cmds, t_envar *envar)
{
	if (cmds[1] == 0)
		return (ft_strdup(getvar(envar, "HOME")));
	if (cmds[1][0] == '-' && cmds[1][1] == 0)
		return (ft_strdup(getvar(envar, "OLDPWD)")));
	if (cmds[1][0] == '-' && cmds[1][1] == '/')
		return (ft_strjoin(getvar(envar, "OLDPWD"), cmds[1] + 1));
	if (cmds[1][0] == '~' && cmds[1][1] == 0)
		return (ft_strdup(getvar(envar, "HOME")));
	if (cmds[1][0] == '~' && cmds[1][1] == '/')
		return (ft_strjoin(getvar(envar, "HOME"), cmds[1] + 1));
	return (ft_strdup(cmds[1]));
}

void		builtincd(char **cmds, t_envar *envar)
{
	char	*dest;

	dest = getdest(cmds, envar);
	move(cmds, dest, envar);
	free(dest);
}
