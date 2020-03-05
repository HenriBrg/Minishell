/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 19:56:01 by hberger           #+#    #+#             */
/*   Updated: 2020/03/05 20:14:50 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	executebuiltins(char **cmds, t_envar *envar, int piped)
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
		builtinexit(cmds, piped);
}

void	pipexec(t_command *tab, t_envar *envar, int piped)
{
	if (isbuiltin(tab->args))
		executebuiltins(tab->args, envar, piped);
	else
		executablesnofork(tab->args, envar);
}
