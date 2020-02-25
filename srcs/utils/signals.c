/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 15:15:08 by hberger           #+#    #+#             */
/*   Updated: 2020/02/25 19:16:50 by hberger          ###   ########.fr       */
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
*/

void	handlesigint(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr("\b\b \n");
		if (g_shellisrunning == 0)
		{
			ft_putstr("------> ");
			g_shellisrunning = 0;
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
			ft_putstr(CLR_LINE);
			ft_putstr(MVCURSOR_BEGL);
			ft_putstr(CLR_LINE_LEFT);
		}
		else
		{
			ft_putstr(MVCURSOR_LEFT);
			ft_putstr(MVCURSOR_LEFT);
			ft_putstr(CLR_LINE_RIGHT);
		}
	}
}

/*
** CTRL + Z == SIGTSTP : Suspendre
*/

void	handlesigtstp(int signal)
{
	if (signal == SIGTSTP)
	{
		if (g_shellisrunning == 1)
		{
			ft_putstr(CLR_LINE);
			ft_putstr(MVCURSOR_BEGL);
			ft_putstr(CLR_LINE_LEFT);
		}
		else
		{
			ft_putstr(MVCURSOR_LEFT);
			ft_putstr(MVCURSOR_LEFT);
			ft_putstr(CLR_LINE_RIGHT);
		}
	}
}

/*
** man signal
** CTRL + C == SIGINT  : Arrêt et prompt
** CTRL + \ == SIGQUIT : Interrompre et prompt
** CTRL + Z == SIGTSTP : Suspendre
*/

void	siglisten(void)
{
	signal(SIGINT, handlesigint);
	signal(SIGQUIT, handlesigquit);
	signal(SIGTSTP, handlesigtstp);
}
