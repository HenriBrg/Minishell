/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_supersplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macasubo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 01:44:19 by macasubo          #+#    #+#             */
/*   Updated: 2020/02/26 04:43:53 by macasubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int		check_spaces(char *str, int n)
{
	int			i;

	i = 0;
	while (str[i] && i < n)
	{
		if (str[i] != '\t' && str[i] != '\n' && str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

static char		*trim_quotes(char *s)
{
	int			len;
	int			state[3];
	int			i;
	int			count;
	char		*new;
// 0 '  1 "  2 

	len = ft_strlen(s);
	i = 0;
	state[0] = 0;
	state[1] = 0;
	state[2] = 0;
	while (i < len)
	{
		if (s[i] == '\\')
		{
			if (state[0] == 0 && state[1] == 0)
			{
				if (state[2] == 0)
				{
					s[i] = 0;
					state[2] = 1;
				}
				else
					state[2] = 0;
			}
		}
		else if (s[i] == '\'')
		{
			if (state[0] == 1)
			{
				state[0] = 0;
				s[i] = 0;
			}
			else
			{
				if (state[1] == 0)
				{
					if (state[2] == 0)
					{
						s[i] = 0;
						state[0] = 1;
						//printf("HI\n");
					}
					else
						state[2] = 0;
				}
			}
		}
		else if (s[i] == '\"')
		{
			if (state[1] == 1)
			{
				state[1] = 0;
				s[i] = 0;
			}
			else
			{
				if (state[0] == 0)
				{
					if (state[2] == 0)
					{
						s[i] = 0;
						state[1] = 1;
					}
					else
						state[2] = 0;
				}
			}
		}
		i++;
	}
	i = 0;
	count = 0;
	while (i < len)
	{
		if (s[i])
			count++;
		i++;
	}
	if (!(new = malloc(sizeof(char) * (count + 1))))
		handle_error(NULL);
	i = 0;
	count = 0;
	while (i < len)
	{
		if (s[i])
		{
			new[count] = s[i];
			count++;
		}
		i++;
	}
	new[count] = 0;
	free(s);
	return (new);
}

void			addback(t_strlist **list, char *str, int n, int trim)
{
	t_strlist	*new;
	t_strlist	*current;

	if (!check_spaces(str, n))
		return ;
	if (!(new = malloc(sizeof(t_strlist))))
		handle_error(NULL);
	if (str)
	{
		if (!(new->str = ft_strsub(str, 0, n)))
			handle_error(NULL);
		if (trim)
			new->str = trim_quotes(new->str);
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

static void		check_separator(t_envsplit *env, int trim)
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
				addback(&(env->list), env->string, env->index, trim);
			if (env->inclusion && env->separators[j][0] != ' ')
				addback(&(env->list), env->string + env->index, len_sep, trim);
			env->string += env->index + len_sep;
			env->index = -1;
			return ;
		}
		j++;
	}
}

#include <stdio.h>

t_strlist		*ft_supersplit(char *string, char **separators, int inclusion,
								int trim)
{
	trim = 0;
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
			check_separator(&env, trim);
		(env.index)++;
	}
	if (env.index != 0 && env.string[0] != 0)
		addback(&(env.list), env.string, env.index, trim);
	return (env.list);
}
