/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:29:47 by hberger           #+#    #+#             */
/*   Updated: 2020/03/10 21:45:40 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char			*finishpath(char **pathtab, char *tmp2)
{
	g_exitvalue = EXIT_SUCCESS;
	ft_strsfree(pathtab);
	return (tmp2);
}

char			*checkpath(char **cmds, struct stat *s, char *envpath)
{
	int			i;
	char		*tmp1;
	char		*tmp2;
	char		**pathtab;

	i = -1;
	if (envpath == 0 || ft_strstr(cmds[0], "./"))
		return (0);
	pathtab = ft_strsplit(envpath, ":");
	while (pathtab[++i])
	{
		tmp1 = ft_strjoin("/", cmds[0]);
		tmp2 = ft_strjoin(pathtab[i], tmp1);
		free(tmp1);
		if (lstat(tmp2, s) == 0)
			if ((s->st_mode & S_IFREG) && (s->st_mode & S_IXUSR))
				return (finishpath(pathtab, tmp2));
		free(tmp2);
	}
	ft_strsfree(pathtab);
	g_exitvalue = 127;
	return (0);
}

void			fornorm(char *execpath)
{
	free(execpath);
	exit(g_exitvalue);
}

void			executablesnofork(char **cmds, t_envar *envar)
{
	char		*execpath;
	struct stat	s;

	if (!(execpath = 0) && ft_strstr(cmds[0], "./") && lstat(cmds[0], &s) == 0)
	{
		if ((s.st_mode & S_IFREG) && (s.st_mode & S_IXUSR))
			execpath = ft_strdup(cmds[0]);
		else
		{
			ft_putstr_fd(cmds[0], 2);
			return (ft_putendl_fd(": Permission denied", 2));
		}
	}
	else if (ft_strstr(cmds[0], "/bin/") && lstat(cmds[0], &s) == 0)
	{
		if ((s.st_mode & S_IFREG) && (s.st_mode & S_IXUSR))
			execpath = ft_strdup(cmds[0]);
	}
	else if ((execpath = checkpath(cmds, &s, getvar(envar, "PATH"))) == 0)
	{
		ft_putstr_fd(cmds[0], 2);
		return (ft_putendl_fd(": command not found", 2));
	}
	g_exitvalue = execve(execpath, cmds, g_environ_strstab);
	fornorm(execpath);
}
