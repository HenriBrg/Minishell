/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macasubo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 19:30:53 by macasubo          #+#    #+#             */
/*   Updated: 2020/02/27 00:49:28 by macasubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_strlist	*parse_commands_bis(t_strlist **pipe_list,
										t_command **supertab)
{
	int				len;
	t_strlist		*current;

	len = 0;
	current = *pipe_list;
	while (current)
	{
		len++;
		current = current->next;
	}
	if (!(*supertab = malloc(sizeof(t_command) * (len + 1))))
		handle_error(NULL);
	(*supertab)[len].args = NULL;
	current = *pipe_list;
	return (current);
}

static void			parse_commands_assign_separators(char **separators)
{
	if (!(separators[0] = ft_strdup(">>")))
		handle_error(NULL);
	if (!(separators[1] = ft_strdup("<")))
		handle_error(NULL);
	if (!(separators[2] = ft_strdup(">")))
		handle_error(NULL);
	separators[3] = NULL;
	separators[4] = NULL;
}

static void			parse_commands_free_separators(char ***separators)
{
	int				i;

	i = 0;
	while ((*separators)[i])
	{
		free((*separators)[i]);
		i++;
	}
	free(*separators);
}

static void			parse_commands_ter(t_strlist *current, t_strlist **command,
										t_command *supertab, int n)
{
	char			**separators;
	char			*new_string;

	if (!(separators = malloc(sizeof(char *) * 5)))
		handle_error(NULL);
	parse_commands_assign_separators(separators);
	*command = ft_supersplit(current->str, separators, 0, 0);
	parse_args(*command, supertab, n);
	if (!(new_string = ft_strsub(current->str, ft_strlen((*command)->str),
				ft_strlen(current->str) - ft_strlen((*command)->str))))
		handle_error(NULL);
	while (*command)
	{
		free((*command)->str);
		free(*command);
		*command = (*command)->next;
	}
	if (!(separators[3] = ft_strdup(" ")))
		handle_error(NULL);
	*command = ft_supersplit(new_string, separators, 1, 0);
	free(new_string);
	parse_commands_free_separators(&separators);
}

t_command			*parse_commands(t_strlist **pipe_list)
{
	t_command		*supertab;
	t_strlist		*current;
	t_strlist		*command;
	int				n;
	t_strlist		*tmp;

	supertab = NULL;
	current = parse_commands_bis(pipe_list, &supertab);
	n = 0;
	while (current)
	{
		command = NULL;
		parse_commands_ter(current, &command, supertab, n);
		parse_redirections(command, supertab, n);
		tmp = current;
		current = current->next;
		free(tmp->str);
		free(tmp);
		n++;
	}
	return (supertab);
}
