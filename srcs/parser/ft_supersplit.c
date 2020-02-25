/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_supersplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macasubo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 01:44:19 by macasubo          #+#    #+#             */
/*   Updated: 2020/02/24 23:01:13 by macasubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void			addback(t_strlist **list, char *str, int n)
{
	t_strlist	*new;
	t_strlist	*current;

	if (!(new = malloc(sizeof(t_strlist))))
		handle_error(NULL);
	if (str)
	{
		if (!(new->str = ft_strsub(str, 0, n)))
			handle_error(NULL);
	}
	else
		new->str = NULL;
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

static void		check_quote(t_envsplit *env)
{
	if (env->quotes[2] == 1)
		env->quotes[2]++;
	else if (env->quotes[2] == 2)
		env->quotes[2] = 0;
	if (env->string[env->index] == '\'')
	{
		if ((env->index > 0 && env->string[env->index - 1] == '\\')
			|| env->quotes[1])
			return ;
		env->quotes[0] = !(env->quotes[0]);
	}
	else if (env->string[env->index] == '\"')
	{
		if ((env->index > 0 && env->string[env->index - 1] == '\\')
			|| env->quotes[0])
			return ;
		env->quotes[1] = !(env->quotes[1]);
	}
	else if (env->string[env->index] == '\\')
	{
		if (env->quotes[2] == 0)
			env->quotes[2] = 1;
	}
}

static void		check_separator(t_envsplit *env)
{
	int			j;
	int			len_sep;

	j = 0;
	while (env->separators[j])
	{
		len_sep = ft_strlen(env->separators[j]);
		if (ft_strncmp(env->string + env->index, env->separators[j], len_sep)
				== 0)
		{
			if (env->index > 0)
				addback(&(env->list), env->string, env->index);
			if (env->inclusion && env->separators[j][0] != ' ')
				addback(&(env->list), env->string + env->index, len_sep);
			env->string += env->index + len_sep;
			env->index = -1;
			return ;
		}
		j++;
	}
}

t_strlist		*ft_supersplit(char *string, char **separators, int inclusion)
{
	t_envsplit	env;

	if (!string || !separators)
		return (NULL);
	env.quotes[0] = 0;
	env.quotes[1] = 0;
	env.quotes[2] = 0;
	env.list = NULL;
	env.index = 0;
	env.string = string;
	env.separators = separators;
	env.inclusion = inclusion;
	while (env.string[env.index])
	{
		check_quote(&env);
		if (!(env.quotes[0]) && !(env.quotes[1]) && !(env.quotes[2]))
			check_separator(&env);
		(env.index)++;
	}
	if (env.index != 0 && env.string[0] != 0)
		addback(&(env.list), env.string, env.index);
	return (env.list);
}
