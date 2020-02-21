/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:29:47 by hberger           #+#    #+#             */
/*   Updated: 2020/02/21 19:48:25 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char			*check(char **cmds, struct stat *s, char *envpath)
{
  int			i;
  char			*tmp1;
  char			*tmp2;
  char			**pathtab;

	i = -1;
	pathtab = ft_strsplit(path, ":");
	while (pathtab[++i])
	{
		tmp1 = ft_strjoin("/", cmds[0]);
		tmp2 = ft_strjoin(pathtab[i], tmp1);
		free(tmp1);
		if (stat(tmp2, s) == 0 && access(tmp2, X_OK) == 0)
			if ((s->st_mode & S_IFREG) && (s->st_mode & S_IXUSR))
			{
				ft_strsfree(pathtab);
				return (tmp2);
	 		}
	}
	ft_strsfree(pathtab);
	ft_putstr("minishell: command not found : ");
	ft_putendl_fd(cmds[0], 1);
	return (0);
}

void			executables(char **cmds, t_envar *envar)
{
	int			returnexec;
	pid_t		pid;
	char		*execpath;
	struct stat	status;

	execpath = 0;
	if ((execpath = check(cmds, &s, getenvar(envar, "PATH"))) == 0)
		return ;
	pid = fork();
	if (pid == 0)
		execv(execpath, cmds);
	else if (pid < 0)
	{
		// ADD WAIT AND FREE
		ft_putstr("Fork Failed\n");
		return (-1);
	}
	wait(&pid);
	return (0);
}
