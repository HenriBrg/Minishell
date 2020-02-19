/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:55:23 by hberger           #+#    #+#             */
/*   Updated: 2020/02/19 18:19:23 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// #include "../inc/minishell.h"
//
// void		prompt(t_list *envar)
// {
// 	char	*tmp;
//
// 	if ((tmp = getvar(envar, "PATH")) == 0)
// 	{
//
// 	}
// }

int			main(int ac, char **av, char **env)
{
	char	*input;
	t_list	*envar;

	(void)ac;
	(void)av;
	if (ac != 1 || (envar = lstenv(env)) == 0)
		return (-1);
	while (42)
	{
		ft_putstr("------> ");
		get_next_line(0, &input);
		if ((parse(input)) == -1)
			return (-1);
		free(input);
	}
	lstclear(envar);
	return (0);
}
