/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 15:15:08 by hberger           #+#    #+#             */
/*   Updated: 2020/02/23 17:23:26 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** Si SIGINT, on n'affichera pas le path au prompt la fonction signal() ne
** prend qu'un seul parametre (int)
** https://stackoverflow.com/questions/2386923
** Gere les 3 signaux
** Signal ne prend pas de pointeur :
** https://stackoverflow.com/questions/6970224/providing-passing-argument-to-signal-handler
*/

void	handlesignals(int signal)
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
	else if (signal == SIGQUIT)
	{
		if (g_shellisrunning == 1)
		{
			ft_putstr(CLR_LINE);
			ft_putstr(MVCURSOR_BEGL);
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
** CTRL + \ == SIGQUIT : Interruption et prompt
** CTRL + Z == SIGTSTP : Interruption
*/

void	siglisten(void)
{
	signal(SIGINT, handlesignals);
	signal(SIGQUIT, handlesignals);
	signal(SIGTSTP, handlesignals);
}
