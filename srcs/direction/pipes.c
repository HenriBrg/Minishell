/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 19:56:01 by hberger           #+#    #+#             */
/*   Updated: 2020/02/25 20:17:12 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** Retourne 1 si cmds[0] fait appel à un builtin
*/

int		isbuiltin(char **cmds)
{
	return (strcmpcasei(cmds[0], "echo") || strcmpcasei(cmds[0], "cd")
			|| strcmpcasei(cmds[0], "pwd") || strcmpcasei(cmds[0], "env")
			|| strcmpcasei(cmds[0], "export") || strcmpcasei(cmds[0], "unset")
			|| strcmpcasei(cmds[0], "exit") ? 1 : 0);
}

/*
** Test chaque builtin
*/

void	executebuiltins(char **cmds, t_envar *envar)
{
	if (strcmpcasei(cmds[0], "echo"))
		builtinecho(cmds, envar);
	else if (strcmpcasei(cmds[0], "cd"))
		builtincd(cmds, envar);
	else if (strcmpcasei(cmds[0], "pwd"))
		builtinpwd(envar);
	else if (strcmpcasei(cmds[0], "unset")
			|| strcmpcasei(cmds[0], "export")
			|| strcmpcasei(cmds[0], "env"))
				builtinsenv(cmds, envar);
	else if (strcmpcasei(cmds[0], "exit"))
		builtinexit(cmds);
}

/*
** Redirige sur un builtin / executable selon les chevrons précisé
*/

void		pipexec(t_command *tab, t_envar *envar)
{
	if (isbuiltin(tab->args))
		executebuiltins(tab->args, envar);
	else
		executables(tab->args, envar);
}

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
** https://www.youtube.com/watch?v=yQLd2iJ9Oa0
*/


void		pipeline(t_command **tab, t_envar *envar)
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
			dup2(backupfd, 0);
			if (*(tab + 1) != NULL)
				dup2(fd[1], 1);
			close(fd[0]);
			pipexec(tab[i], envar);
			exit((g_exitvalue = EXIT_FAILURE));
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
