/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:10:59 by hberger           #+#    #+#             */
/*   Updated: 2020/02/20 22:00:42 by macasubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#include <stdio.h>

/*static void			parse_redirections(t_strlist *command, t_command *supertab,
											int n)
{
	
}*/

static void			parse_args(t_strlist *command, t_command *supertab, int n)
{
	t_strlist		*args;
	t_strlist		*tmp;
	char			*separators[] = {" ", "\t", NULL};
	int				len;
	int				i;

	if (command)
	{
		printf("command str : %s\n", command->str);
		args = ft_supersplit(command->str, separators, 0, "");
		len = 0;
		tmp = args;
		while (tmp)
		{
			len++;
			tmp = tmp->next;
		}
		printf("nb arg : %d\n", len);
		if (!(supertab[n].args = malloc(sizeof(char *) * (len + 1))))
			handle_error(NULL);
		//printf("len : %d\n", len);
		supertab[n].args[len] = NULL;
		i = 0;
		while (args && *(args->str))
		{
			supertab[n].args[i] = ft_strdup(args->str);
			//printf("n : %d\there : %s\n", n, *(supertab[n].args));
			//printf("ft_strlen(arg) : %zu\n", ft_strlen(*(supertab[n].args)));
			i++;
			tmp = args;
			args = args->next;
			free(tmp->str);
			free(tmp);
		}
	}
}

static t_command	*parse_commands(t_strlist **pipe_list)
{
	t_command		*supertab;
	t_strlist		*current;
	t_strlist		*command;
	char			*separators[] = {"<", ">", ">>", NULL};
	int				len;
	int				n;
	t_strlist		*tmp;

	len = 0;
	current = *pipe_list;
	while (current)
	{
		len++;
		current = current->next;
	}
	if (!(supertab = malloc(sizeof(t_command) * (len + 1))))
		handle_error(NULL);
	supertab[len].args = NULL;
	current = *pipe_list;
	n = 0;
	while (current)
	{
		//printf("debug 1\n");
		command = ft_supersplit(current->str, separators, 1, ""); // 2nd split
		parse_args(command, supertab, n); // commande splitee par chevrons
		command = command->next;
		//parse_redirections(command, supertab, n);
		tmp = current;
		current = current->next;
		free(tmp->str);
		free(tmp);
		n++;
	}
	return (supertab);
}

int					parse(char *input)
{
	char			*separators[] = {"|", NULL};
	t_strlist		*pipe_list;
	t_command		*supertab;
	int				i;
	int				j;

	// avant : verifier le format de la ligne
	pipe_list = ft_supersplit(input, separators, 0, ""); // pipe parsing
	supertab = parse_commands(&pipe_list);
	// apres : pour chaque maillon faire un split et l'envoyer dans un tableau
	// de structures, puis free la liste chainee

	i = 0;
	j = 0;
	while (supertab[i].args)
	{
		while (supertab[i].args[j])
		{
			printf("%s\n", supertab[i].args[j]);
			j++;
		}
		printf("---------\n");
		j = 0;
		i++;
	}
	/*while (pipe_list)
	{
		printf("%s\n", pipe_list->str);
		pipe_list = pipe_list->next;
	}*/

	/*int	i = 0;
	while (pipes[i])
	{
		printf("%s\n", pipes[i]);
		i++;
	}*/
	return (0);
}
