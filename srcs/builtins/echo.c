/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:11:47 by hberger           #+#    #+#             */
/*   Updated: 2020/02/20 19:12:11 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		is_n_option(int i, char **cmd_tab)
{
	int	j;
	int	k;

	j = 0;
	while (++j <= i)
	{
		if (!ft_str_start_with(cmd_tab[j], "-n"))
			return (0);
		k = 1;
		while (cmd_tab[j][++k])
		{
			if (cmd_tab[j][k] != 'n')
				return (0);
		}
	}
	return (1);
}

/*
** no_option_n()
**
** NB :
** echo a b c -n l'option doit se situer avant les arguments donc
** else if (i > 1)
**    return (0);
*/

int		nflag(char **cmds)
{
	int i;

	i = 0;
	while (cmds[++i])
	{
		if (is_n_option(i, cmds))
			return (0);
		else if (i > 1)
			return (1);
	}
	return (1);
}

/* TODO

~ v9 > echo ls > tmp
~ v9 > sh < tmp
Makefile	libft		srcs
includes	minishell	tmp

*/

/*
** echo() print chaque argument séparé d'un espace
** puis un \n sauf si flag -n
** echo -n -n n'affiche rien
** i = 0 car on saute le "echo"
**
** TODO : gerer $value
*/

void	builtinecho(char **cmds, t_envar *envar)
{
	int		i;
	char	**args;

	i = 0;
	if (cmds[1] == 0)
		return (ft_putstr("\n"));
	while (args[++i])
	{
		if (ft_strlen(args[i]) == 0 || is_n_option(i, args))
			continue ;
		else if (i > 1 && !is_n_option(i - 1, args))
			write(1, " ", 1);
		write(1, args[i], ft_strlen(args[i]));
	}
	write(1, "\n", nflag(args));
	ft_free_str_tab(args);
	// REMEMBER $?
}
