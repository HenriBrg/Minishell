/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:10:59 by hberger           #+#    #+#             */
/*   Updated: 2020/02/21 04:25:29 by macasubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#include <stdio.h>

static void			parse_redirections(t_strlist *command, t_command *supertab,
											int n)
{
	t_strlist		*tmp;
	int				in;
	int				out;
	int				len;
	int				index;
	char			**new_args;

	supertab[n].out = NULL;
	supertab[n].in = NULL;
	in = 0;
	out = 0;
	while (command)
	{
		if (ft_strcmp(command->str, "<") == 0)
		{
			if (in != 0 || out != 0)
				handle_error("bash: syntax error near unexpected token \'<\'");
			in = 1;
		}
		else if (ft_strcmp(command->str, ">") == 0)
		{
			if (in != 0 || out != 0)
				handle_error("bash: syntax error near unexpected token \'>\'");
			out = 1;
		}
		else if (ft_strcmp(command->str, ">>") == 0)
		{
			if (in != 0 || out != 0)
				handle_error("bash: syntax error near unexpected token \'>>\'");
			out = 2;
		}
		else
		{
			if (in == 1)
			{
				addback(&(supertab[n].in), command->str,
							ft_strlen(command->str), 0);
				in = 0;
			}
			else if (out == 1)
			{
				addback(&(supertab[n].out), command->str,
							ft_strlen(command->str), 1);
				out = 0;
			}
			else if (out == 2)
			{
				addback(&(supertab[n].out), command->str,
							ft_strlen(command->str), 2);
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
		printf("command str : %s\n", command->str);
		args = ft_supersplit(command->str, separators, 0, "");
		len = 0;
		tmp = args;
		while (tmp)
		{
			printf("tmp : %s\n", tmp->str);
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
		//printf("debug 1\n");
		command = ft_supersplit(current->str, separators1, 0, ""); // 2nd split
		parse_args(command, supertab, n); // commande splitee par chevrons
		//tmp = command;
		//command = command->next;
		//free(tmp->str);
		//free(tmp);
		new_string = ft_strsub(current->str, ft_strlen(command->str),
								ft_strlen(current->str) - ft_strlen(command->str));
		printf("new string : %s\n", new_string);
		// free all the tab (command)
		command = ft_supersplit(new_string, separators2, 1, "");
		parse_redirections(command, supertab, n);
		tmp = current;
		current = current->next;
		free(tmp->str);
		free(tmp);
		n++;
	}
	return (supertab);
}

t_command			*parse(char *input)
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
		printf("----- ARGS -----\n");
		while (supertab[i].args[j])
		{
			printf("%s\n", supertab[i].args[j]);
			j++;
		}
		printf("----- INS -----\n");
		while (supertab[i].in)
		{
			printf("%s\n", supertab[i].in->str);
			supertab[i].in = supertab[i].in->next;
		}
		printf("----- OUTS -----\n");
		while (supertab[i].out)
		{
			printf("%s\n", supertab[i].out->str);
			supertab[i].out = supertab[i].out->next;
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
	return (supertab);
}
