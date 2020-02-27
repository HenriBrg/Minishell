/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:55:23 by hberger           #+#    #+#             */
/*   Updated: 2020/02/26 22:54:13 by hberger          ###   ########.fr       */
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

void		monoprocess(t_command *tab, t_envar *envar)
{
	int fd;

	fd = nopiped_chevrons(tab, envar);
	if (isbuiltin(tab->args))
		executebuiltins(tab->args, envar);
	else
		executables(tab->args, envar);
	dup2(fd, 1);
	//dup2(0, 0);

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
	//input = malloc(sizeof(char **));
	input = NULL;
	if (ac != 1 || (envar = lstenv(env)) == 0)
		return (-1);
	siglisten();
	while (42)
	{
		//printf("YO\n");
		prompt(envar);
		g_shellisrunning = 0;
		get_next_line(0, &input);
		//printf("input : %s\n", input);

		list = parse(input); // AJOUTER EXIT $?
		//printf("input : %s\n", input);
		//printf("BONJOUR\n");
		//printf("%s\n", (char *)list);
		// les maillons de list sont separes par un ;
		// les cases du tableau dans chacun des maillon sont des |
		// a l'interieur de chacune des cases : tableau des args, entree et sortie
		// valeurs de out_type : 0 pour aucun, 1 pour > et 2 pour >>
		// exemple de parcours dans la fonction parse()
		// commande de test :
		// echo salut < in comment >> out ca va | head < in > out | less moi ca va > out bien < in ; sort il fait > out ; cat >> out tres beau < in ajd | echo >> out en effet < in oui

		// iterer sur la liste chainees de ;

		if (list && list->command)
		{
			cmds = list->command[0].args;
			g_shellisrunning = 1;

			int countpipe = 0;
			while (list->command[countpipe].args != NULL)
				countpipe++;
			//	printf("pipe : %d\n", countpipe);
			if (countpipe <= 1) // zero processus
			{
				printf("monprocess\n");
				monoprocess(list->command, envar);
			}
			else
			{
				printf("multiprocess\n");
				pipeline(list->command, envar);

			}
		}
		if (input)
			free(input);
	}
	lstclear(envar);
	return (0);
}
