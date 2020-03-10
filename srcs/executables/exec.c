/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:29:47 by hberger           #+#    #+#             */
/*   Updated: 2020/03/10 18:46:39 by hberger          ###   ########.fr       */
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
	pathtab = ft_strsplit(envpath, ":");
	while (pathtab[++i])
	{
		tmp1 = ft_strjoin("/", cmds[0]);
		tmp2 = ft_strjoin(pathtab[i], tmp1);
		free(tmp1);
		if (stat(tmp2, s) == 0)
			if ((s->st_mode & S_IFREG) && (s->st_mode & S_IXUSR))
				return (finishpath(pathtab, tmp2));
		free(tmp2);
	}
	ft_strsfree(pathtab);
	// ft_putstr_fd("minishell: ", 2);
	// ft_putstr_fd(cmds[0], 2);
	// ft_putendl_fd(": command not found", 2);
	g_exitvalue = 127;
	return (0);
}

void			executablesnofork(char **cmds, t_envar *envar)
{
	int			ret;
	char		*fullpath;
	char		*execpath;
	struct stat	s;

	execpath = 0;
	fullpath = getvar(envar, "PATH");
	if ((execpath = checkpath(cmds, &s, fullpath)) == 0)
	{
		if (stat(cmds[0], &s) == 0)
			if ((s.st_mode & S_IFREG) && (s.st_mode & S_IXUSR))
				execpath = ft_strdup(cmds[0]);
		if (execpath == 0)
		{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmds[0], 2);
				ft_putendl_fd(": No such file or directory", 2);
				return ;
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmds[0], 2);
			ft_putendl_fd(": command not found", 2);
		}
	}

	// if (stat(cmds[0], &s) == 0)
	// {
	// 	if ((s.st_mode & S_IFREG) && (s.st_mode & S_IXUSR))
	// 		execpath = ft_strdup(cmds[0]);
	// }
	// else if (fullpath == NULL)
	// {
	// 	ft_putstr_fd("minishell: ", 2);
	// 	ft_putstr_fd(cmds[0], 2);
	// 	ft_putendl_fd(": No such file or directory", 2);
	// 	return ;
	// }
	// else if ((execpath = checkpath(cmds, &s, fullpath)) == 0)
	// 	return ;
	ret = execve(execpath, cmds, g_environ_strstab);
	free(execpath);
	exit((g_exitvalue = ret));
}
