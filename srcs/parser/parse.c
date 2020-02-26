/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:10:59 by hberger           #+#    #+#             */
/*   Updated: 2020/02/26 19:00:27 by macasubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#include <stdio.h>

static void			parse_args_bis(t_strlist *args, t_command *supertab,
									t_strlist *tmp, char **separators)
{
	int				i;

	i = 0;
	while (args && *(args->str))
	{
		supertab->args[i] = ft_strdup(args->str);
		i++;
		tmp = args;
		args = args->next;
		free(tmp->str);
		free(tmp);
	}
	free(separators[0]);
	free(separators[1]);
	free(separators);
}

void				parse_args(t_strlist *command, t_command *supertab, int n)
{
	t_strlist		*args;
	t_strlist		*tmp;
	char			**separators;
	int				len;

	if (command)
	{
		if (!(separators = malloc(sizeof(char *) * 3)))
			handle_error(NULL);
		if (!(separators[0] = ft_strdup(" ")))
			handle_error(NULL);
		if (!(separators[1] = ft_strdup("\t")))
			handle_error(NULL);
		separators[2] = NULL;
		args = ft_supersplit(command->str, separators, 0, 0);
		len = 0;
		tmp = args;
		while (tmp)
		{
			len++;
			tmp = tmp->next;
		}
		if (!(supertab[n].args = malloc(sizeof(char *) * (len + 1))))
			handle_error(NULL);
		supertab[n].args[len] = NULL;
		parse_args_bis(args, supertab + n, tmp, separators);
	}
}

static void			addback_command(t_commands_list **list, t_command *command)
{
	t_commands_list	*new;
	t_commands_list	*current;

	if (!(new = malloc(sizeof(t_commands_list))))
		handle_error(NULL);
	new->command = command;
	new->next = NULL;
	current = *list;
	if (!current)
		*list = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

static void			top_level_parsing(t_strlist **semicolon_list,
									char **separators, t_commands_list **list)
{
	t_strlist		*pipe_list;
	t_command		*supertab;
	t_strlist		*tmp;

	pipe_list = ft_supersplit((*semicolon_list)->str, separators, 0, 0);
	supertab = parse_commands(&pipe_list);
	addback_command(list, supertab);
	tmp = *semicolon_list;
	*semicolon_list = (*semicolon_list)->next;
	free(tmp->str);
	free(tmp);
}

t_commands_list		*parse(char *input)
{
	char			**separators;
	t_strlist		*semicolon_list;
	t_commands_list	*list;
	int				i;
	int				j;

	if (!(separators = malloc(sizeof(char *) * 2)) || !(separators[0] =
			ft_strdup(";")))
		handle_error(NULL);
	separators[1] = NULL;
	semicolon_list = ft_supersplit(input, separators, 0, 0);
	list = NULL;
	free(separators[0]);
	if (!(separators[0] = ft_strdup("|")))
		handle_error(NULL);
	while (semicolon_list)
		top_level_parsing(&semicolon_list, separators, &list);
	free(separators[0]);
	free(separators);

	t_commands_list *cur = list;
	while (cur)
	{
		i = 0;
		while (cur->command[i].args)
	 	{
	 		printf("----- ARGS -----\n");
	 		j = 0;
	 		while (cur->command[i].args[j])
	 		{
				cur->command[i].args[j] = trim_quotes(cur->command[i].args[j]);
	 			printf("%s\n", cur->command[i].args[j]);
	 			j++;
	 		}
	 		printf("----- IN -----\n");
	 		printf("%s\n", cur->command[i].in);
	 		printf("----- OUT -----\n");
	 		printf("%s\n", cur->command[i].out);
	 		printf("---------END OF COMMAND---------\n");
	 		i++;
	 	}
		printf("---------END OF SEMICOLON---------\n");
		cur = cur->next;
	}
	return (list);
}
