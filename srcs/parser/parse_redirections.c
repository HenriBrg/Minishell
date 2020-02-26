/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macasubo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:36:17 by macasubo          #+#    #+#             */
/*   Updated: 2020/02/26 19:21:38 by macasubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#include <stdio.h>

static int			handle_chevrons(t_strlist *command, int *in, int *out)
{
	if (ft_strcmp(command->str, "<") == 0)
	{
		if (*in != 0 || *out != 0)
			handle_error("minishell: syntax error near unexpected token \'<\'");
		*in = 1;
		return (1);
	}
	else if (ft_strcmp(command->str, ">") == 0)
	{
		if (*in != 0 || *out != 0)
			handle_error("minishell: syntax error near unexpected token \'>\'");
		*out = 1;
		return (1);
	}
	else if (ft_strcmp(command->str, ">>") == 0)
	{
		if (*in != 0 || *out != 0)
			handle_error("minishel: syntax error near unexpected token \'>>\'");
		*out = 2;
		return (1);
	}
	return (0);
}

static int			handle_path(t_command *supertab, t_strlist *command,
								int *in, int *out)
{
	if (*in == 1)
	{
		//if (supertab->in)
		//	handle_error("minishell: fd aggregation not supported");
		//if (!(supertab->in = ft_strdup(command->str)))
		//	handle_error(NULL);
		addback(&(supertab->in), command->str, ft_strlen(command->str), 0);
		*in = 0;
		return (1);
	}
	else if (*out == 1 || *out == 2)
	{
		//if (supertab->out)
		//	handle_error("minishell: fd aggregation not supported");
		//if (!(supertab->out = ft_strdup(command->str)))
		//	handle_error(NULL);
		//supertab->out_type = *out;
		addback(&(supertab->out), command->str, ft_strlen(command->str), 0);
		supertab->out->out_type = *out;
		*out = 0;
		return (1);
	}
	return (0);
}

static void			handle_parameter(t_command *supertab, int n,
									t_strlist *command)
{
	int				len;
	int				index;
	char			**new_args;

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

void				parse_redirections(t_strlist *command, t_command *supertab,
										int n)
{
	t_strlist		*tmp;
	int				in;
	int				out;

	supertab[n].out = NULL;
	supertab[n].in = NULL;
	in = 0;
	out = 0;
	while (command)
	{
		if (!handle_chevrons(command, &in, &out))
			if (!handle_path(supertab + n, command, &in, &out))
				handle_parameter(supertab, n, command);
		tmp = command;
		command = command->next;
		free(tmp->str);
		free(tmp);
	}
}
