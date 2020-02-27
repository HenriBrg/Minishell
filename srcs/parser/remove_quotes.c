/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macasubo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:48:00 by macasubo          #+#    #+#             */
/*   Updated: 2020/02/27 02:04:30 by macasubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void		substitute_variable(char **s, int *i, int *len, t_envar *envar)
{
	int			len_var_name;
	char		*var_name;
	char		*var_subst;
	char		*a;
	char		*c;
	char		*new_string;
	char		*tmp;

	(*i)++;
	len_var_name = 0;
	while ((*s)[*i + len_var_name] && (*s)[*i + len_var_name] != '\'' &&
			(*s)[*i + len_var_name] != '\"' && (*s)[*i + len_var_name] != '\\'
			&& (*s)[*i + len_var_name] != '$')
		len_var_name++;
	var_name = ft_strsub(*s, *i, len_var_name);
	new_string = NULL;
	a = NULL;
	c = NULL;
	var_subst = NULL;
	tmp = NULL;
	var_subst = getvar(envar, var_name);
	if (var_name)
		free(var_name);
	if (*i - 1 > 0)
	{
		if (!(a = ft_strsub(*s, 0, *i - 1)))
			handle_error(NULL);
	}
	else 
		a = NULL;
//	printf("var_subst : %s\n", var_subst);
	//printf("a : %s\n", a);
	if (ft_strlen(*s + *i + len_var_name) > 0)
	{
		if (!(c = ft_strsub(*s, *i + len_var_name,
				ft_strlen(*s + *i + len_var_name))))
			handle_error(NULL);
	}
	else
		c = NULL;
	//printf("c : %s\n", c);
	if (!a && !var_subst)
		tmp = NULL;
	else if (!a)
		tmp = ft_strdup(var_subst);
	else if (!var_subst)
		tmp = ft_strdup(a);
	else
	{
		if (!(tmp = ft_strjoin(a, var_subst)))
			handle_error(NULL);
	}		//printf("tmp : %s\n", tmp);
	if (!tmp && !c)
		new_string = ft_strdup("");
	else if (!tmp)
		new_string = ft_strdup(c);
	else if (!c)
		new_string = ft_strdup(tmp);
	else
	{
		if (!(new_string = ft_strjoin(tmp, c)))
			handle_error(NULL);
	}
	//printf("new_string : %s\n", new_string);
	*i = -1;
	if (tmp)
		*i += ft_strlen(tmp);
	*len = 0;
	if (new_string)
		*len = ft_strlen(new_string);
	free(*s);
	*s = new_string;
	//printf("final string : %s\n", *s);
	//printf("i : %d ; len : %d\n", *i, *len);
//	printf("var_subst : %s\n", var_subst);
	if (a)
		free(a);
	if (c)
		free(c);
//	if (var_subst)
//		free(var_subst);
	//printf("debug 3\n");
	if (tmp)
		free(tmp);
	//printf("debug 4\n");
}

char			*trim_quotes(char *s, t_envar *envar)
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
		else if (s[i] == '$' && s[i + 1] && s[i + 1] != '\'' && s[i + 1] != '\"'
					&& s[i + 1] != '\\')
		{
			if (state[2] == 0 && state[0] == 0)
			{
				s[i] = 0;
				substitute_variable(&s, &i, &len, envar);
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
