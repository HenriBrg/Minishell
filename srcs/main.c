/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:55:23 by hberger           #+#    #+#             */
/*   Updated: 2020/05/06 21:54:43 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void			prompt(t_envar *envar)
{
	ft_putstr_fd(getvar(envar, "PWD"), 2);
	ft_putstr_fd("/ ------> ", 2);
	g_shellisrunning = 0;
}

static int			monoprocess(t_command *tab, t_envar *envar)
{
	if (strcmpcasei(tab->args[0], "unset") || strcmpcasei(tab->args[0], "cd")
	|| strcmpcasei(tab->args[0], "export") || strcmpcasei(tab->args[0], "exit"))
	{
		executebuiltins(tab->args, envar, 0);
		return (1);
	}
	return (0);
}

static void			shell(char *input, t_envar *envar)
{
	t_commands_list		*list;
	t_commands_list		*tmp;
	int			countpipe;

	list = NULL;
	if (onlyfdout(input) == 1)
		return ;
	list = parse(input, envar);
	tmp = list;
	while (tmp)
	{
		if (tmp->command && tmp->command[0].args)
		{
			g_shellisrunning = 1;
			countpipe = 0;
			while (tmp->command[countpipe].args != NULL)
				countpipe++;
			if (!(countpipe - 1 == 0 && monoprocess(tmp->command, envar)))
				pipeline(tmp->command, envar, countpipe - 1);
		}
		tmp = tmp->next;
	}
	commands_lstclear(list);
}

int				main(int ac, char **av, char **env)
{
	int			ret;
	char			*input;
	t_envar			*envar;

	(void)av;
	envar = NULL;
	input = NULL;
	if (ac != 1 || (envar = lstenv(env)) == 0)
		return (-1);
	siglisten();
	g_shellisrunning = 0;
	g_environ_strstab = env;
	while (42)
	{
		prompt(envar);
		ret = get_next_line(0, &input);
		g_shellisrunning = 1;
		if (ret <= 0 && write(2, "exit\n", 5))
			exit((g_exitvalue = EXIT_SUCCESS));
		shell(input, envar);
		if (input)
			free(input);
	}
	lstclear(envar);
	return (0);
}
