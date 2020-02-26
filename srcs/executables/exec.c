/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:29:47 by hberger           #+#    #+#             */
/*   Updated: 2020/02/26 18:41:39 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** Leaks to handle
*/

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

	if ((i = -1) && stat(cmds[0], s) == 0 && access(cmds[0], F_OK | X_OK) == 0)
		if ((s->st_mode & S_IFREG) && (s->st_mode & S_IXUSR))
			return (ft_strdup(cmds[0]));
	pathtab = ft_strsplit(envpath, ":");
	while (pathtab[++i])
	{
		tmp1 = ft_strjoin("/", cmds[0]);
		tmp2 = ft_strjoin(pathtab[i], tmp1);
		free(tmp1);
		if (stat(tmp2, s) == 0 && access(tmp2, F_OK | X_OK) == 0)
			if ((s->st_mode & S_IFREG) && (s->st_mode & S_IXUSR))
				return (finishpath(pathtab, tmp2));
		free(tmp2);
	}
	ft_strsfree(pathtab);
	ft_putstr("minishell: command not found : ");
	ft_putendl_fd(cmds[0], 1);
	g_exitvalue = 127;
	return (0);
}

/*
** 1) On recupere le path
** 2) On fork et en cas de succes (pid == 0) on execv
** 3) Sinon on exit ou wait la fin du fork
*/

void			executables(char **cmds, t_envar *envar)
{
	int			ret;
	int			wpid;
	pid_t		pid;
	char		*execpath;
	struct stat	s;

	execpath = 0;
	wpid = 0;
	if ((execpath = checkpath(cmds, &s, getvar(envar, "PATH"))) == 0)
		return ;
	pid = fork();
	if (pid == 0)
	{
		// Change into execv
		// How free an allocation going to exec ? In the parent I guess ?
		// printf("%s\n", tab->args);
		ret = execve(execpath, cmds, NULL);
		// printf("ret = %d\n", ret);
		free(execpath);
		exit((g_exitvalue = EXIT_FAILURE));
	}
	else if (pid == -1)
		exit(EXIT_FAILURE);
	else
		waitpid(pid, &wpid, 0);
		//free ici ?
}
