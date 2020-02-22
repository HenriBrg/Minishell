/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 15:15:08 by hberger           #+#    #+#             */
/*   Updated: 2020/02/22 16:29:06 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"



///// WTF : https://stackoverflow.com/questions/6970224/providing-passing-argument-to-signal-handler

/*
** https://stackoverflow.com/questions/2386923
** Gere les 3 signaux
*/

void	handlesignals(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr("\b\b  \n");
		// if (!g_shellisrunning)
		// 	prompt();
	}
	else if (signal == SIGQUIT)
	{
		if (g_shellisrunning)
		{
			//ft_putstr(CLR_LINE);
			//ft_putstr(MVCURSOR_BEGL);
		}
		else
		{
			//ft_putstr(MVCURSOR_LEFT);
			//ft_putstr(MVCURSOR_LEFT);
			//ft_putstr(CLR_LINE_RIGHT);
		}
	}
}

/*
** man signal
** CTRL + C == SIGINT
** CTRL + \ == SIGQUIT
** CTRL + Z == SIGTSTP
*/

void	siglisten(void)
{
	signal(SIGINT, handlesignals);
	signal(SIGQUIT, handlesignals);
	signal(SIGTSTP, handlesignals);
}
