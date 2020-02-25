/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 19:56:01 by hberger           #+#    #+#             */
/*   Updated: 2020/02/25 17:54:19 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** Loop sur le tableau de commande séparé par des pipes
**
** typedef struct			s_command
** {
** 	char					**args;
** 	int						out_type;
** 	char					*out;
** 	char					*in;
** }						t_command; // No list but tab for link
**
** https://gist.github.com/iomonad/a66f6e9cfb935dc12c0244c1e48db5c8
** Le child lit - Le parent ecrit : https://www.youtube.com/watch?v=yQLd2iJ9Oa0
*/

void		pipeline(t_command **tab)
{
	int		i;
	int		fd[2];
	int		backupfd;
	pid_t	pid;

	i = 0;
	backupfd = 0;
	while (tab[i] != 0)
	{
		pipe(fd);
		if ((pid = fork()) == -1)
			exit((g_exitvalue = EXIT_FAILURE));
		else if (pid == 0)
		{
			// Child - Looped
			dup2(backupfd, 0); // Duplication de STDIN
			if (*(tab + 1) != NULL) // If other pipe :
				dup2(fd[1], 1);
			close(fd[0]);

			// CALL EXECUTABLES OR BUILTINS with tab->args

			exit((g_exitvalue = EXIT_SUCCESS));
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			backupfd = fd[0];
			i++;
		}
	}
}
