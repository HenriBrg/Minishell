/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 20:58:19 by hberger           #+#    #+#             */
/*   Updated: 2020/05/02 16:57:23 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** switchdir() verifie la destination puis change de dossier
*/

static int		switchdir(char **cmds, char *dest)
{
	int			i;

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

static char		*getdest(char **cmds, t_envar *envar)
{
	if (cmds[1] == 0)
		return (finishgetdest(envar, "HOME", 0));
	if (cmds[1][0] == '.' && cmds[1][1] == 0)
		return (finishgetdest(envar, "PWD", 0));
	if (cmds[1][0] == '-' && cmds[1][1] == 0)
		return (finishgetdest(envar, "OLDPWD", 1));
	if (cmds[1][0] == '~' && cmds[1][1] == 0)
		return (finishgetdest(envar, "HOME", 0));
	if (cmds[1][0] == '~' && cmds[1][1] == '/')
		return (ft_strjoin(finishgetdest(envar, "HOME", 0), cmds[1] + 1));
	return (ft_strdup(cmds[1]));
}

void			competemove(t_envar *envar, char *currentworkdir)
{
	char		*exportation;
	char		**exportcmds;
	char		buf[PATH_MAX - 1];

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

static void		move(char **cmds, char *dest, t_envar *envar)
{
	char		*tmp;
	static int	except;
	char		*currentworkdir;
	char		buf[PATH_MAX - 1];

	currentworkdir = 0;
	if ((currentworkdir = getcwd(buf, PATH_MAX - 1)) == 0)
	{
		tmp = getdest(cmds, envar);
		if (except && ft_strcmp(getvar(envar, "PWD"), tmp) != 0)
			chdir(getdest(cmds, envar));
		else
		{
			except = 1;
			ft_putstr_fd("cd: error retrieving current directory", 2);
			ft_putstr_fd(": getcwd: cannot access", 2);
			ft_putstr_fd(" parent directories: No such file or directory\n", 2);
		}
		return ;
	}
	except = 0;
	if (dest == 0 || switchdir(cmds, dest) == 1)
		return ;
	competemove(envar, currentworkdir);
}

void			builtincd(char **cmds, t_envar *envar)
{
	char		*dest;

	dest = getdest(cmds, envar);
	move(cmds, dest, envar);
	free(dest);
}
