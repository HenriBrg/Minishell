/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:55:23 by hberger           #+#    #+#             */
/*   Updated: 2020/02/21 16:07:54 by hberger          ###   ########.fr       */
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

int		executebuiltins(char **cmds, t_envar *envar)
{
	// i = 0;
	// while (cmds[i])
	// {
	// 	printf("%s\n", cmds[i]);
	// 	i++;
	// }

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
	return (1);
}



int			main(int ac, char **av, char **env)
{
	char	*input;
	t_envar	*envar;

	// tmp for test
	char	**cmds;

	(void)ac;
	(void)av;
	if (ac != 1 || (envar = lstenv(env)) == 0)
		return (-1);
	//listen();
	while (42)
	{
		prompt(envar);
		get_next_line(0, &input);
		//if ((parse(input)) == -1)
		//	return (-1);

		// tmp for test
		cmds = ft_strsplit(input, " ");
		if (isbuiltin(cmds))
			executebuiltins(cmds, envar);
		ft_strsfree(cmds);
		// execute ();
		free(input);
	}
	lstclear(envar);
	return (0);
}
