/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macasubo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 01:54:40 by macasubo          #+#    #+#             */
/*   Updated: 2020/05/01 15:36:17 by macasubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

static char		*substitute_variable_bis(char **s, int *i, t_envsubvar *env)
{
	char		*var_name;

	var_name = NULL;
	(*s)[*i] = 0;
	(*i)++;
	while ((*s)[*i + env->len_var_name] && (*s)[*i + env->len_var_name] != '\''
			&& (*s)[*i + env->len_var_name] != '\"' && (*s)[*i +
			env->len_var_name] != '\\' && (*s)[*i + env->len_var_name] != '$'
			&& (*s)[*i + env->len_var_name] != ' ')
		(env->len_var_name)++;
	if ((*s)[*i] != '?')
		var_name = ft_strsub(*s, *i, env->len_var_name);
	return (var_name);
}

static char		*substitute_variable_ter(int *i, char **s, t_envsubvar *env)
{
	char		*c;

	if (*i - 1 > 0)
	{
		if (!(env->a = ft_strsub_ignore_null(*s, 0, *i - 1)))
			handle_error(NULL);
	}
	else
		env->a = NULL;
	if (ft_strlen(*s + *i + env->len_var_name) > 0)
	{
		if (!(c = ft_strsub(*s, *i + env->len_var_name,
				ft_strlen(*s + *i + env->len_var_name))))
			handle_error(NULL);
	}
	else
		c = NULL;
	return (c);
}

static char		*substitute_variable_quater(t_envsubvar *env)
{
	char		*new_string;

	if (!(env->a) && !(env->var_subst))
		env->tmp = NULL;
	else if (!(env->a))
		env->tmp = ft_strdup(env->var_subst);
	else if (!(env->var_subst))
		env->tmp = ft_strdup(env->a);
	else
	{
		if (!(env->tmp = ft_strjoin(env->a, env->var_subst)))
			handle_error(NULL);
	}
	if (!(env->tmp) && !(env->c))
		new_string = ft_strdup("");
	else if (!(env->tmp))
		new_string = ft_strdup(env->c);
	else if (!(env->c))
		new_string = ft_strdup(env->tmp);
	else
	{
		if (!(new_string = ft_strjoin(env->tmp, env->c)))
			handle_error(NULL);
	}
	return (new_string);
}

static void		substitute_variable_quinquies(char **s, int *i, int *len,
												t_envsubvar *env)
{
	if ((*s)[*i] == '?')
		free(env->var_subst);
	*i = -1;
	if (env->tmp)
		*i += ft_strlen(env->tmp);
	*len = 0;
	if (env->new_string)
		*len = ft_strlen(env->new_string);
}

void			substitute_variable(char **s, int *i, int *len, t_envar *envar)
{
	t_envsubvar	env;

	env.len_var_name = 0;
	env.var_name = substitute_variable_bis(s, i, &env);
	env.a = NULL;
	env.var_subst = NULL;
	env.tmp = NULL;
	if ((*s)[*i] == '?')
		env.var_subst = ft_itoa(g_exitvalue);
	else
		env.var_subst = getvar(envar, env.var_name);
	if (env.var_name)
		free(env.var_name);
	env.c = substitute_variable_ter(i, s, &env);
	env.new_string = substitute_variable_quater(&env);
	substitute_variable_quinquies(s, i, len, &env);
	free(*s);
	*s = env.new_string;
	if (env.a)
		free(env.a);
	if (env.c)
		free(env.c);
	if (env.tmp)
		free(env.tmp);
}
