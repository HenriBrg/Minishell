/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:55:23 by hberger           #+#    #+#             */
/*   Updated: 2020/02/23 17:26:35 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
** Ajouter le path ...
*/

void		prompt(t_envar *envar)
{
	(void)envar;
	ft_putstr(getvar(envar, "PWD"));
	ft_putstr("/ ------> ");
}

/*
** Retourne 1 si cmds[0] fait appel à un builtin
*/

int		isbuiltin(char **cmds)
{
	return (strcmpcasei(cmds[0], "echo") || strcmpcasei(cmds[0], "cd")
			|| strcmpcasei(cmds[0], "pwd") || strcmpcasei(cmds[0], "env")
			|| strcmpcasei(cmds[0], "export") || strcmpcasei(cmds[0], "unset")
			|| strcmpcasei(cmds[0], "exit") ? 1 : 0);
}

/*
**
*/

void	executebuiltins(char **cmds, t_envar *envar)
{
	if (strcmpcasei(cmds[0], "echo"))
		builtinecho(cmds, envar);
	else if (strcmpcasei(cmds[0], "cd"))
		builtincd(cmds, envar);
	else if (strcmpcasei(cmds[0], "pwd"))
		builtinpwd(envar);
	else if (strcmpcasei(cmds[0], "unset")
			|| strcmpcasei(cmds[0], "export")
			|| strcmpcasei(cmds[0], "env"))
				builtinsenv(cmds, envar);
	else if (strcmpcasei(cmds[0], "exit"))
		builtinexit(cmds);
}



int			main(int ac, char **av, char **env)
{
	char	*input;
	t_envar	*envar;

	char	**cmds;

	(void)ac;
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
		
		//if ((parse(input)) == -1)
		//	return (-1);

		if (ft_strlen(input) != 0)
		{
			cmds = ft_strsplit(input, " ");
			g_shellisrunning = 1;
			if (isbuiltin(cmds))
				executebuiltins(cmds, envar);
			else
				executables(cmds, envar);
			ft_strsfree(cmds);
		}
		free(input);
	}
	lstclear(envar);
	return (0);
}
