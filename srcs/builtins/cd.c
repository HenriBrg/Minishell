/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 20:58:19 by hberger           #+#    #+#             */
/*   Updated: 2020/02/19 23:16:19 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** switchdir() verifie la destination puis change de dossier
*/

int		switchdir(char **cmds, char *dest)
{
	int i;

	i = chdir(dest);
	if (i == 0) // SET EXIT FAILURE VALUE (global variable)
		return (-1);
	else
	{
		ft_putstr("cd: ");
		if (access(dest, F_OK) == -1)
			ft_putstr("no such file or directory: ");
		else if (access(dest, R_OK) == -1)
			ft_putstr("permission denied: ");
		else
			ft_putstr("not a directory: ");
		if (cmds[1])
			ft_putendl_fd(cmds[1]);
		else
			ft_putendl_fd(dest);
		// SET EXIT FAILURE VALUE (global variable)
		return (0);
	}
}

/*
** char *getcwd(char *buf, size_t size);
** En cas de réussite buf est renvoyé.
** NULL en cas d'échec, avec errno contenant le code d'erreur.
** Le contenu de la chaîne pointée par buf est indéfini en cas d'erreur.
**
** TODO : errno
** 4096 = MAX PATH
**
*/

void	move(char **cmds, char *dest)
{
	char	*tmp;
	char	buf[PATH_MAX - 1];
	char	*exportation;
	char	**exportcmds;

	tmp = getcwd(buf, PATH_MAX - 1);
	if (dest == 0 || switchdir(cmds, dest) == -1)
		return ;
	exportation = ft_strjoin("export OLDPWD=", tmp);
	exportcmds = ft_strsplit(exportation, " ");
	// CALL EXPORT BUILTIN
	free(exportation);
	ft_strsfree(exportcmds);
	tmp = getcwd(buf, PATH_MAX - 1);
	exportation = ft_strjoin("export PWD=", tmp);
	exportcmds = ft_split(exportation, ' ');
	// CALL EXPORT BUILTIN
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
** TODO : Gérer le cd $VAR d'environnement ?
*/

char	*getdest(char **cmds, t_list *envar)
{
	if (cmds[1] == 0)
		return (getvar("HOME"));
	if (cmds[1][0] == '-' && cmds[1][1] == 0)
	{
		ft_putendl_fd(getvar("OLDPWD"), 1);
		return (getvar("OLDPWD"));
	}
	if (cmds[1][0] == '-' && cmds[1][1] == '/')
	{
		ft_putendl_fd(getvar("OLDPWD"), 1);
		return (ft_strjoin(getvar("OLDPWD"), cmds[1] + 1));
	}
	if (cmds[1][0] == '~' && cmds[1][1] == 0)
		return (getvar("HOME"));
	if (cmds[1][0] == '~' && cmds[1][1] == '/')
		return (ft_strjoin(getvar("HOME"), cmds[1] + 1));
	if (ft_strncmp(cmds[1], "$HOME") == 0)
		return (getvar("HOME"));
	return (cmds[1]);
}

/*
** 1) On cherche le path
** 2) On bouge
*/

void	cd(char **cmds, t_list *envar)
{
	char	*dest;

	dest = getdest(cmds, envar);
	move(cmds, path);
}
