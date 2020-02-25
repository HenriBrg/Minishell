/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:10:59 by hberger           #+#    #+#             */
/*   Updated: 2020/02/25 01:27:34 by macasubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#include <stdio.h>

static void			parse_redirections(t_strlist *command, t_command *supertab,
											int n)
{
	t_strlist		*tmp;
	int				len;
	int				index;
	char			**new_args;
	int				in;
	int				out;

	supertab[n].out = NULL;
	supertab[n].in = NULL;
	supertab[n].out_type = 0;
	in = 0;
	out = 0;
	while (command)
	{
		if (ft_strcmp(command->str, "<") == 0)
		{
			if (in != 0 || out != 0)
				handle_error("minishell: syntax error near unexpected token \'<\'");
			in = 1;
		}
		else if (ft_strcmp(command->str, ">") == 0)
		{
			if (in != 0 || out != 0)
				handle_error("minishell: syntax error near unexpected token \'>\'");
			out = 1;
		}
		else if (ft_strcmp(command->str, ">>") == 0)
		{
			if (in != 0 || out != 0)
				handle_error("minishel: syntax error near unexpected token \'>>\'");
			out = 2;
		}
		else
		{
			if (in == 1)
			{
				if (supertab[n].in)
					handle_error("minishell: fd aggregation not supported");
				if (!(supertab[n].in = ft_strdup(command->str)))
					handle_error(NULL);
				in = 0;
			}
			else if (out == 1)
			{
				if (supertab[n].out)
					handle_error("minishell: fd aggregation not supported");
				if (!(supertab[n].out = ft_strdup(command->str)))
					handle_error(NULL);
				supertab[n].out_type = 1;
				out = 0;
			}
			else if (out == 2)
			{
				if (supertab[n].out)
					handle_error("minishell: fd aggregation not supported");
				if (!(supertab[n].out = ft_strdup(command->str)))
					handle_error(NULL);
				supertab[n].out_type = 2;
				out = 0;
			}
			else
			{
				len = 0;
				index = 0;
				while (supertab[n].args[len])
					len++;
				if (!(new_args = malloc(sizeof(char *) * (len + 2))))
					handle_error(NULL);
				new_args[len + 1] = NULL;
				while (supertab[n].args[index])
				{
					new_args[index] = ft_strdup(supertab[n].args[index]);
					free(supertab[n].args[index]);
					index++;
				}
				new_args[index] = ft_strdup(command->str);
				free(supertab[n].args);
				supertab[n].args = new_args;
			}
		}
		tmp = command;
		command = command->next;
		free(tmp->str);
		free(tmp);
	}
}

static void			parse_args(t_strlist *command, t_command *supertab, int n)
{
	t_strlist		*args;
	t_strlist		*tmp;
	char			*separators[] = {" ", NULL};
	int				len;
	int				i;

	if (command)
	{
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
		i = 0;
		while (args && *(args->str))
		{
			supertab[n].args[i] = ft_strdup(args->str);
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
	char			*separators1[] = {">>", "<", ">", NULL};
	char			*separators2[] = {">>", "<", ">", " ", NULL};
	int				len;
	int				n;
	t_strlist		*tmp;
	char			*new_string;

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
	char			*separators1[] = {"|", NULL};
	char			*separators2[] = {";", NULL};
	t_strlist		*pipe_list;
	t_command		*supertab;
	t_strlist		*semicolon_list;
	t_strlist		*tmp;
	t_commands_list	*list;
	int				i;
	int				j;

	semicolon_list = ft_supersplit(input, separators2, 0);
	list = NULL;
	while (semicolon_list)
	{
		pipe_list = ft_supersplit(semicolon_list->str, separators1, 0);
		supertab = parse_commands(&pipe_list);
		addback_command(&list, supertab);
		tmp = semicolon_list;
		semicolon_list = semicolon_list->next;
		free(tmp->str);
		free(tmp);
	}

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
