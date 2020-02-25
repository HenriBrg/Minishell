/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:55:23 by hberger           #+#    #+#             */
/*   Updated: 2020/02/25 05:06:45 by macasubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
** Ajouter le path ...
*/

void		prompt(t_envar *envar)
{
	(void)envar;
	ft_putstr("------> ");
}

int			main(int ac, char **av, char **env)
{
	char	*input;
	t_envar	*envar;
	t_commands_list	*list;

	(void)ac;
	(void)av;
	if (ac != 1 || (envar = lstenv(env)) == 0)
		return (-1);
	//listen();
	while (42)
	{
		prompt(envar);
		get_next_line(0, &input);
		list = parse(input);
		while (1);
		// les maillons de list sont separes par un ;
		// les cases du tableau dans chacun des maillon sont des |
		// a l'interieur de chacune des cases : tableau des args, entree et sortie
		// valeurs de out_type : 0 pour aucun, 1 pour > et 2 pour >>
		// exemple de parcours dans la fonction parse()
// commande de test :
// echo salut < in comment >> out ca va | head < in > out | less moi ca va > out bien < in ; sort il fait > out ; cat >> out tres beau < in ajd | echo >> out en effet < in oui
		free(input);
		// execute ();
	}
	lstclear(envar);
	return (0);
}
