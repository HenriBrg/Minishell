/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:55:23 by hberger           #+#    #+#             */
/*   Updated: 2020/03/03 04:14:58 by macasubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
** Affiche le prompteur
*/

void				prompt(t_envar *envar)
{
	(void)envar;
	ft_putstr(getvar(envar, "PWD"));
	ft_putstr("/ ------> ");
}

/*
** Pas d'appel de builtins pour l'instant
*/

int					setfds(t_command *tab, t_envar *envar)
{
	int				fd;
	int				pid;
	t_strlist		*tmp;


	if ((pid = fork()) < 0)
		exit(1);
	else if (pid == 0)
	{
		tmp = tab[0].out;
		while (tmp)
		{
			fd = open(tmp->str, O_CREAT | O_WRONLY | (tmp->out_type == 2 ? O_APPEND : O_TRUNC), 0777);
			if (tmp->next == 0 && fd != -1)
			{
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
			tmp = tmp->next;
		}

		tmp = tab[0].in;
		while (tmp)
		{
			fd = open(tmp->str, O_RDONLY, 0777);
			if (tmp->next == 0 && fd != -1)
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			tmp = tmp->next;
		}

		if (isbuiltin(tab->args))
		{
			executebuiltins(tab->args, envar);
			exit(0);
		}
		else
		{
			char		*execpath;
			struct stat	s;

			execpath = 0;
			if ((execpath = checkpath(tab->args, &s, getvar(envar, "PATH"))) == 0)
				return -1;
			printf("execpath = %s\n", execpath);
			execve(execpath, tab->args, NULL);
			exit((g_exitvalue = EXIT_FAILURE));
		}
	}
	else
		wait(NULL);
	return (0);
}

void				monoprocess(t_command *tab, t_envar *envar)
{
	if (strcmpcasei(tab->args[0], "unset") || strcmpcasei(tab->args[0], "cd")
		|| strcmpcasei(tab->args[0], "export") || strcmpcasei(tab->args[0], "exit"))
		{
			printf("unset exit export cd\n");
			executebuiltins(tab->args, envar);
		}
	else
		setfds(tab, envar);

}

/*
**
*/

int					main(int ac, char **av, char **env)
{
	char			*input;
	t_envar			*envar;
	t_commands_list	*list;
	t_commands_list	*tmp;

	char			**cmds;
	(void)av;
	envar = NULL;
	input = NULL;
	if (ac != 1 || (envar = lstenv(env)) == 0)
		return (-1);
	siglisten();
	while (42)
	{
		prompt(envar);
		g_shellisrunning = 0;
		get_next_line(0, &input);
		list = NULL;
		list = parse(input, envar);
		// les maillons de list sont separes par un ;
		// les cases du tableau dans chacun des maillon sont des |
		// a l'interieur de chacune des cases : tableau des args, entree et sortie
		// valeurs de out_type : 0 pour aucun, 1 pour > et 2 pour >>
		// commande de test :
		// echo salut < in comment >> out ca va | head < in > out | less moi ca va > out bien < in ; sort il fait > out ; cat >> out tres beau < in ajd | echo >> out en effet < in oui

		// iterer sur la liste chainees de ;

		tmp = list;
		while (tmp)
		{
			if (tmp->command && tmp->command[0].args)
			{
				cmds = tmp->command[0].args;
				g_shellisrunning = 1;

				int countpipe = 0;
				while (tmp->command[countpipe].args != NULL)
					countpipe++;
				if (countpipe <= 1) // zero processus
				{
					monoprocess(tmp->command, envar);
				}
				else
				{
					pipeline(tmp->command, envar, countpipe - 1);
				}
			}
			tmp = tmp->next;
		}
		commands_lstclear(list);
		if (input)
			free(input);
	}
	lstclear(envar);
	return (0);
}
