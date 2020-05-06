/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 15:15:08 by hberger           #+#    #+#             */
/*   Updated: 2020/05/06 22:52:19 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** Si SIGINT, on n'affichera pas le path au prompt la fonction signal() ne
** prend qu'un seul parametre (int)
** https://stackoverflow.com/questions/2386923
** Gere les 3 signaux
** Signal ne prend pas de pointeur :
** https://stackoverflow.com/questions/6970224/providing-passing-
** argument-to-signal-handler
** ft_putstr("\b\b \n") ----> https://abs.traduc.org/abs-5.3-fr/abs-5.3.pdf
** (backspace non destructif)
** ft_putstr("\b\b  \n");
*/

void	handlesigint(int signal)
{
	if (signal == SIGINT)
	{
		if (g_shellisrunning == 1)
		{
			ft_putstr("\n");
			g_shellisrunning = 0;
			g_exitvalue = 130;
		}
		else
		{
			ft_putstr_fd("\n------> ", 2);
			g_exitvalue = 130;
		}
	}
}

/*
** CTRL + \ == SIGQUIT : Interrompre et prompt
*/

void	handlesigquit(int signal)
{
	if (signal == SIGQUIT)
	{
		if (g_shellisrunning == 1)
		{
			ft_putstr_fd("Quit: 3\n", 2);
			g_shellisrunning = 0;
			g_exitvalue = 131;
		}
	}
}

/*
** man signal
** CTRL + C == SIGINT  : Arrêt et prompt
** CTRL + \ == SIGQUIT : Interrompre et prompt
*/

void	siglisten(void)
{
	signal(SIGINT, handlesigint);
	signal(SIGQUIT, handlesigquit);
}
