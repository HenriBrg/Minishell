/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:10:59 by hberger           #+#    #+#             */
/*   Updated: 2020/02/25 05:03:52 by macasubo         ###   ########.fr       */
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
	free(separators);
}

static void			parse_args(t_strlist *command, t_command *supertab, int n)
{
	t_strlist		*args;
	t_strlist		*tmp;
	char			**separators;
	int				len;

	if (command)
	{
		if (!(separators = malloc(sizeof(char *) * 2)) || !(separators[0] =
			ft_strdup(" ")))
			handle_error(NULL);
		separators[1] = NULL;
		args = ft_supersplit(command->str, separators, 0);
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

/*static void			parse_commands_bis(t_strlist *current, t_command *supertab,
										int *n, char **separators)
{
	char			*new_string;
	t_strlist		*tmp;
	t_strlist		*command;

	command = ft_supersplit(current->str, separators, 0);
	parse_args(command, supertab, *n);
	if (!(new_string = ft_strsub(current->str, ft_strlen(command->str),
				ft_strlen(current->str) - ft_strlen(command->str))))
		handle_error(NULL);
	while (command)
	{
		free(command->str);
		free(command);
		command = command->next;
	}
	if (!(separators[3] = ft_strdup(" ")))
		handle_error(NULL);
	command = ft_supersplit(new_string, separators, 1);
	free(new_string);
	parse_redirections(command, supertab, *n);
	tmp = current;
	current = current->next;
	free(tmp->str);
	free(tmp);
	(*n)++;
}*/

static t_command	*parse_commands(t_strlist **pipe_list)
{
	t_command		*supertab;
	t_strlist		*current;
	t_strlist		*command;
	char			*separators1[] = {">>", "<", ">", NULL};
	char			*separators2[] = {">>", "<", ">", " ", NULL};
	int				len;
	int				n;
	t_strlist		*tmp;
	char			*new_string;
	//char			**separators;

	len = 0;
	current = *pipe_list;
	while (current)
	{
		len++;
		current = current->next;
	}
	if (!(supertab = malloc(sizeof(t_command) * (len + 1)))/* || !(separators =
		malloc(sizeof(char *) * 5)) || !(separators[0] = ft_strdup(">>")) ||
		!(separators[1] = ft_strdup("<")) || !(separators[2] = ft_strdup(">"))
		|| (separators[3] = NULL) || (separators[4] = NULL)*/)
		handle_error(NULL);
	supertab[len].args = NULL;
	current = *pipe_list;
	n = 0;
	while (current)
	{
		command = ft_supersplit(current->str, separators1, 0);
		parse_args(command, supertab, n);
		if (!(new_string = ft_strsub(current->str, ft_strlen(command->str),
					ft_strlen(current->str) - ft_strlen(command->str))))
			handle_error(NULL);
		while (command)
		{
			free(command->str);
			free(command);
			command = command->next;
		}
		command = ft_supersplit(new_string, separators2, 1);
		free(new_string);
		parse_redirections(command, supertab, n);
		tmp = current;
		current = current->next;
		free(tmp->str);
		free(tmp);
		n++;
		//parse_commands_bis(current, supertab, &n separators);
	}
	return (supertab);
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

t_commands_list		*parse(char *input)
{
	char			**separators;
	t_strlist		*pipe_list;
	t_command		*supertab;
	t_strlist		*semicolon_list;
	t_strlist		*tmp;
	t_commands_list	*list;
	int				i;
	int				j;

	if (!(separators = malloc(sizeof(char *) * 2)) || !(separators[0] =
			ft_strdup(";")))
		handle_error(NULL);
	separators[1] = NULL;
	semicolon_list = ft_supersplit(input, separators, 0);
	list = NULL;
	free(separators[0]);
	if (!(separators[0] = ft_strdup("|")))
		handle_error(NULL);
	while (semicolon_list)
	{
		pipe_list = ft_supersplit(semicolon_list->str, separators, 0);
		supertab = parse_commands(&pipe_list);
		addback_command(&list, supertab);
		tmp = semicolon_list;
		semicolon_list = semicolon_list->next;
		free(tmp->str);
		free(tmp);
	}
	free(separators[0]);
	free(separators);

	t_commands_list *cur = list;
	while (cur)
	{
		i = 0;
		j = 0;
		while (cur->command[i].args)
		{
			printf("----- ARGS -----\n");
			j = 0;
			while (cur->command[i].args[j])
			{
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
