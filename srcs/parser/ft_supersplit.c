#include "../../inc/minishell.h"

#include <stdio.h>
/*
static void		rm_chars(char **str)
{
	int			simple_quote;
	int			double_quote;
	char		*s;
	int			len;
	int			index;

	simple_quote = 0;
	double_quote = 0;
	len = ft_strlen(*str);
	index = 0;
	while (index < len)
	{
		if ((*str)[index] == '\'')
		{
			if (double_quote == 0 && !(index > 0 && (*str)[index - 1] == 0))
			{
				(*str)[index] = 0;
				simple_quote = !simple_quote;
			}
			
		}
		else if ((*str)[index] == '\"')
		{
			if (simple_quote == 0 && !(index > 0 && (*str)[index - 1] == 0))
			{
				(*str)[index] = 0;
				double_quote = !double_quote;
			}
		}
		else if ((*str)[index] == '\\')
		{
			if (!(index > 0 && (*str)[index - 1] == 0))
				(*str)[index] = 0;
		}
		index++;
	}
	index = 0;
	while (len--)
		if ((*str)[len] != 0)
			index++;
	if (!(s = malloc(sizeof(char) * (index + 1))))
		return ; // handle error
	len = 0;
	while (index)
	{
		if (**str != 0)
		{
			s[len] = **str;
			index--;
			len++;
		}
		(*str)++;
	}
	s[len] = 0;
	free(*str);
	*str = s;
}
*/
static void		addback(t_strlist **list, char *str, int n)
{
	t_strlist	*new;
	t_strlist	*current;

	if (!(new = malloc(sizeof(t_strlist))))
		handle_error(NULL);
	if (str)
	{
		new->str = ft_strsub(str, 0, n);
		//rm_chars(&str);
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
		if (ft_strncmp(env->string + env->index, env->separators[j], len_sep) == 0)
		{
			addback(&(env->list), env->string, env->index);
			if (env->inclusion)
				addback(&(env->list), env->string + env->index, len_sep);
			env->string += env->index + len_sep;
			env->index = -1;
			return ;
		}
		j++;
	}
}

t_strlist		*ft_supersplit(char *string, char **separators, int inclusion
								, char *trim)
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
	env.trim = trim;
	while (string[env.index])
	{
		check_quote(&env);
		if (!(env.quotes[0]) && !(env.quotes[1]) && !(env.quotes[2]))
			check_separator(&env);
		(env.index)++;
	}
	if (env.index != 0)
		addback(&(env.list), env.string, env.index);
	return (env.list);
}
