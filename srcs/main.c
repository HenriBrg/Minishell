/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:55:23 by hberger           #+#    #+#             */
/*   Updated: 2020/03/04 22:01:46 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void				prompt(t_envar *envar)
{
	ft_putstr(getvar(envar, "PWD"));
	ft_putstr("/ ------> ");
}

int					monoprocess(t_command *tab, t_envar *envar)
{
	if (strcmpcasei(tab->args[0], "unset")
		|| strcmpcasei(tab->args[0], "cd")
		|| strcmpcasei(tab->args[0], "export")
		|| strcmpcasei(tab->args[0], "exit"))
		{
			executebuiltins(tab->args, envar, 0);
			return (1);
		}
	return (0);
}

/*
**
** les maillons de list sont separes par un ;
** les cases du tableau dans chacun des maillon sont des |
** a l'interieur de chacune des cases : tableau des args, entree et sortie
** valeurs de out_type : 0 pour aucun, 1 pour > et 2 pour >>
** commande de test :
** echo salut < in comment >> out ca va | head < in > out | less moi ca va > out bien < in ; sort il fait > out ; cat >> out tres beau < in ajd | echo >> out en effet < in oui
** iterer sur la liste chainees de ;
*/

int					main(int ac, char **av, char **env)
{
	char			*input;
	t_envar			*envar;
	t_commands_list	*list;
	t_commands_list	*tmp;
	int 			countpipe;

	(void)av;
	envar = NULL;
	input = NULL;
	if (ac != 1 || (envar = lstenv(env)) == 0)
		return (-1);
	siglisten();
	g_environ_strstab = env;
	while (42)
	{
		prompt(envar);
		g_shellisrunning = 0;
		if (get_next_line(0, &input) == 0)
		{
			ft_putstr("exit");
			exit((g_exitvalue = EXIT_SUCCESS));
		}
		list = NULL;
		list = parse(input, envar);
		tmp = list;
		while (tmp)
		{
			if (tmp->command && tmp->command[0].args)
			{
				g_shellisrunning = 1;
				countpipe = 0;
				while (tmp->command[countpipe].args != NULL)
					countpipe++;
				pipeline(tmp->command, envar, countpipe - 1);
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
