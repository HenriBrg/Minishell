/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipesbis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macasubo <macasubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:50:33 by macasubo          #+#    #+#             */
/*   Updated: 2020/03/05 18:13:42 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void		handle_in_redirection(t_command *tab, int i, int pipefds[])
{
	t_strlist	*tmp;
	int			fd;
	int			redirin;

	redirin = 0;
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
	if (i != 0 && !redirin)
		if (dup2(pipefds[(i - 1) * 2], 0) == -1)
			handle_error(NULL);
}

static void		handle_out_redirection(t_command *tab, int i, int pipefds[])
{
	t_strlist	*tmp;
	int			fd;
	int			redirout;

	redirout = 0;
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
	if (tab[i + 1].args && !redirout)
		if (dup2(pipefds[i * 2 + 1], 1) == -1)
			handle_error(NULL);
}

static void		pipeline_bis(int nbpipes, int pipefds[])
{
	int			j;
	int			status;

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
		j++;
	}
}

static void		close_pipefds(int nbpipes, int pipefds[])
{
	int			j;

	j = -1;
	while (++j < 2 * nbpipes)
		if ((close(pipefds[j])) == -1)
			handle_error(NULL);
}

void			pipeline(t_command *tab, t_envar *envar, int nbpipes)
{
	int			pipefds[2 * nbpipes];
	int			i;
	pid_t		pid;

	i = -1;
	while (++i < nbpipes)
		if (pipe(pipefds + i * 2) == -1)
			handle_error(NULL);
	i = 0;
	while (tab[i].args)
	{
		if ((pid = fork()) == -1)
			handle_error(NULL);
		else if (pid == 0)
		{
			handle_in_redirection(tab, i, pipefds);
			handle_out_redirection(tab, i, pipefds);
			close_pipefds(nbpipes, pipefds);
			pipexec(tab + i, envar, 1);
			exit(g_exitvalue);
		}
		i++;
	}
	pipeline_bis(nbpipes, pipefds);
}
