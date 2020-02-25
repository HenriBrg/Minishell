/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 20:58:19 by hberger           #+#    #+#             */
/*   Updated: 2020/02/25 18:56:28 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** switchdir() verifie la destination puis change de dossier
*/

int			switchdir(char **cmds, char *dest)
{
	int		i;

	i = chdir(dest);
	if (i == 0)
	{
		g_exitvalue = EXIT_SUCCESS;
		return (0);
	}
	else
	{
		ft_putstr("cd: ");
		if (cmds[1])
			ft_putstr(cmds[1]);
		else
			ft_putstr(dest);
		ft_putstr(": ");
		if (access(dest, F_OK) == -1)
			ft_putstr("No such file or directory\n");
		else if (access(dest, R_OK) == -1)
			ft_putstr("Permission denied\n");
		else
			ft_putstr("Not a directory\n");
		g_exitvalue = EXIT_FAILURE;
		return (-1);
	}
}

/*
** char *getcwd(char *buf, size_t size);
** En cas de réussite buf est renvoyé.
** NULL en cas d'échec, avec errno contenant le code d'erreur.
** Le contenu de la chaîne pointée par buf est indéfini en cas d'erreur.
** TODO : errno
*/

void		move(char **cmds, char *dest, t_envar *envar)
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

/*
** getdest() retourne le path vers lequel aller
** Cas possible : 'cd'
** Cas possible : 'cd -'
** Cas possible : 'cd ~'
** Cas possible : 'cd -/[...]'
** Cas possible : 'cd ~/[...]'
** Cas possible : 'cd $HOME[...]'
**
** >>>>>>>>>>>>>>>>> Leaks to handle
** >>>>>>>>>>>>>>>>> Leaks to handle
*/

char		*getdest(char **cmds, t_envar *envar)
{
	if (cmds[1] == 0)
		return (getvar(envar, "HOME"));
	if (cmds[1][0] == '-' && cmds[1][1] == 0)
		return (getvar(envar, "OLDPWD"));
	if (cmds[1][0] == '-' && cmds[1][1] == '/')
		return (ft_strjoin(getvar(envar, "OLDPWD"), cmds[1] + 1));
	if (cmds[1][0] == '~' && cmds[1][1] == 0)
		return (getvar(envar, "HOME"));
	if (cmds[1][0] == '~' && cmds[1][1] == '/')
		return (ft_strjoin(getvar(envar, "HOME"), cmds[1] + 1));
	if (ft_strncmp(cmds[1], "$HOME", 5) == 0)
		return (getvar(envar, "HOME"));
	return (cmds[1]);
}

/*
** 1) On cherche le path
** 2) On bouge
*/

void		builtincd(char **cmds, t_envar *envar)
{
	char	*dest;

	dest = getdest(cmds, envar);
	move(cmds, dest, envar);
}
