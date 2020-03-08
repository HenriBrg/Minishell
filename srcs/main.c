/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:55:23 by hberger           #+#    #+#             */
/*   Updated: 2020/03/08 22:17:53 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void			prompt(t_envar *envar)
{
	ft_putstr_fd(getvar(envar, "PWD"), 1);
	ft_putstr_fd("/ ------> ", 1);
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
	t_commands_list	*list;
	t_commands_list	*tmp;
	int				countpipe;

	list = NULL;
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


/*
**  char	*readline(char *intput)
**  {
**  	if (ret == -1)
**  		exit((g_exitvalue = EXIT_SUCCESS));
**  	if (ret == 0 && ft_strlen(input))
**  	{
**  		eof = 1;
**  		ft_putstr_fd("  \b\b", 2);
**  	}
**  	if (ret == 0 && ft_strlen(input) == 0)
**  	{
**  		ft_putstr_fd("  \b\b", 2);
**  		exit((g_exitvalue = EXIT_SUCCESS));
**  	}
**
**  }
 */


static int previousiseof(int *ret, int *eof)
 {
 	char		*bef_line;
 	char		*new_line;

 	bef_line = input;
 	new_line = 0;
 	if ((*ret = get_next_line(0, &new_line)) < 0)
		exit(EXIT_FAILURE);
 	if (!(input = ft_strjoin(bef_line, new_line)))
		exit(EXIT_FAILURE);
 	free(bef_line);
 	free(new_line);
 	if (*ret > 0)
 		*eof = 0;
 	if (*ret == 0)
 	{
 		ft_putstr("  \b\b");
 		return (0);
 	}
 	return (1);
 }
static int currentlinehandle(int *ret, int *eof)
 {
 	*ret = get_next_line(0, &input);
 	if (*ret == -1)
 		exit(-1);
 	if ((*ret == 0 && ft_strlen(input)))
 	{
 		*eof = 1;
 		ft_putstr("  \b\b");
 		return (0);
 	}
 	if (*ret == 0 && !ft_strlen(input))
 	{
 		ft_putstr("  \b\b");
		ft_putstr("\n");
		exit(0);
 	}
 	return (1);
 }

 int				readinput(void)
 {
	 static int	ret;
	 static int	eof;

	if (eof)
	{
		write(1, "***", 3);

		if (!previousiseof(&ret, &eof))
			return (0);

	}
	else
	{
		write(1, "---", 3);

		if (!currentlinehandle(&ret, &eof))
			return (0);
	}
	return (1);
 }

int					main(int ac, char **av, char **env)
{
	//int				ret;
	//char			*input;
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
		// ret = get_next_line(0, &input);
		g_shellisrunning = 1;
		// if (ret <= 0 && write(2, "exit\n", 5))
		// 	exit((g_exitvalue = EXIT_SUCCESS));
		if (!readinput())
			continue ;
		if (0)
			shell(input, envar);
		if (input)
			free(input);
	}
	lstclear(envar);
	return (0);
}
