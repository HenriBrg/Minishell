/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:55:23 by hberger           #+#    #+#             */
/*   Updated: 2020/02/25 20:45:00 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char		*replacedollars(char **cmds, t_envar *envar)
{
	(void)cmds;
	(void)envar;
	// penser aussi a $? (globale)
	return 0;
}

/*
** Affiche le prompteur
*/

void		prompt(t_envar *envar)
{
	(void)envar;
	ft_putstr(getvar(envar, "PWD"));
	ft_putstr("/ ------> ");
}

/*
**
*/

int			main(int ac, char **av, char **env)
{
	char			*input;
	t_envar			*envar;
	t_commands_list	*list;

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

		list = parse(input); // AJOUTER EXIT $?
		cmds = list->command[0].args;
		// les maillons de list sont separes par un ;
		// les cases du tableau dans chacun des maillon sont des |
		// a l'interieur de chacune des cases : tableau des args, entree et sortie
		// valeurs de out_type : 0 pour aucun, 1 pour > et 2 pour >>
		// exemple de parcours dans la fonction parse()
		// commande de test :
		// echo salut < in comment >> out ca va | head < in > out | less moi ca va > out bien < in ; sort il fait > out ; cat >> out tres beau < in ajd | echo >> out en effet < in oui

		g_shellisrunning = 1;

		pipeline(list->command, envar);
		// if (isbuiltin(cmds))
		// 	executebuiltins(cmds, envar);
		// else
		// 	executables(cmds, envar);
		free(input);
	}
	lstclear(envar);
	return (0);
}
