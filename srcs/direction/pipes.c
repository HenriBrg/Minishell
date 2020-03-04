/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 19:56:01 by hberger           #+#    #+#             */
/*   Updated: 2020/03/04 22:50:38 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** Retourne 1 si cmds[0] fait appel à un builtin
*/

int			isbuiltin(char **cmds)
{
	return (strcmpcasei(cmds[0], "echo") || strcmpcasei(cmds[0], "cd")
			|| strcmpcasei(cmds[0], "pwd") || strcmpcasei(cmds[0], "env")
			|| strcmpcasei(cmds[0], "export") || strcmpcasei(cmds[0], "unset")
			|| strcmpcasei(cmds[0], "exit") ? 1 : 0);
}

void	executebuiltins(char **cmds, t_envar *envar, int piped)
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
		builtinexit(cmds, piped);
}

void		pipexec(t_command *tab, t_envar *envar, int piped)
{
	if (isbuiltin(tab->args))
		executebuiltins(tab->args, envar, piped);
	else
		executablesnofork(tab->args, envar);
}

/*void			pipeline(t_command *tab, t_envar *envar, int nbpipes)
{
	int			pipefds[2 * nbpipes];
	int			i;
	int			j;
	pid_t		pid;
	int			status;
	t_strlist	*tmp;
	int			fd;
	int			redirin;
	int			redirout;

	if (nbpipes == 0 && monoprocess(tab, envar))
		return ;
	i = 0;
	while (i < nbpipes) // On cree d'abord tous les pipes
	{
		if (pipe(pipefds + i * 2) == -1)
			handle_error(NULL);
		i++;
	}
	i = 0;
	//redirout = 0;
	while (tab[i].args) // On itere sur les commandes
	{
		redirin = 0;
		redirout = 0;
		if ((pid = fork()) == -1) // Fork
			handle_error(NULL);
		else if (pid == 0) // Child process
		{
			tmp = tab[i].in;
			if (tmp)
			{
				while (tmp->next)
					tmp = tmp->next;
				if ((fd = open(tmp->str, O_RDONLY)) == -1)
					handle_error(NULL);
				if ((dup2(fd, 0)) == -1)
					handle_error(NULL);
				if ((close(fd)) == -1)
					handle_error(NULL);
				redirin = 1;
			}
			tmp = tab[i].out;
			while (tmp)
			{
				if ((fd = open(tmp->str, O_CREAT | O_WRONLY |
					(tmp->out_type == 2 ? O_APPEND : O_TRUNC), 0777)) == -1)
					handle_error(NULL);
				if (!(tmp->next))
				{
					if ((dup2(fd, 1)) == -1)
						handle_error(NULL);
					if ((close(fd)) == -1)
						handle_error(NULL);
					redirout = 1;
				}
				tmp = tmp->next;
			}
			if (i != 0 && !redirin)
				if (dup2(pipefds[(i - 1) * 2], 0) == -1) // Dup 0 > stdin de la cmd
					handle_error(NULL);
			if (tab[i + 1].args && !redirout)
			{
				if (dup2(pipefds[i * 2 + 1], 1) == -1) // Dup 1 > stdout de la cmd
					handle_error(NULL);
			}
			j = 0;
			while (j < 2 * nbpipes)
			{
				if ((close(pipefds[j])) == -1)
					handle_error(NULL);
				j++;
			}
			pipexec(tab + i, envar, 1);
			exit(g_exitvalue);
			//(void)envar;
			//execvp(*(tab[i].args), tab[i].args);
			//handle_error(NULL);
		}
		i++;
	}
	j = 0;
	while (j < 2 * nbpipes)
	{
		if ((close(pipefds[j])) == -1)
			handle_error(NULL);
		j++;
	}
	j = 0;
	while (j < nbpipes + 1)
	{
		wait(&status);
		g_exitvalue = WEXITSTATUS(status);
		//printf("status : %d\n", WEXITSTATUS(status));
		j++;
	}
}*/
