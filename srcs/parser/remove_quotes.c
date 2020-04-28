/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macasubo <macasubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:48:00 by macasubo          #+#    #+#             */
/*   Updated: 2020/04/28 20:10:13 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int		trim_quotes_antislash(char *s, int i, int state[3])
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
		return (1);
	}
	return (0);
}

static int		trim_quotes_simple(char *s, int i, int state[3])
{
	if (s[i] == '\'')
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
				}
				else
					state[2] = 0;
			}
		}
		return (1);
	}
	return (0);
}

static int		trim_quotes_double(char *s, int i, int state[3])
{
	if (s[i] == '\"')
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
		return (1);
	}
	return (0);
}

static char		*trim_quotes_final(int len, char *s)
{
	int			i;
	int			count;
	char		*new;

	i = -1;
	count = 0;
	while (++i < len)
		if (s[i])
			count++;
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

char			*trim_quotes(char *s, t_envar *envar)
{
	int			len;
	int			state[3];
	int			i;
	char		*new;

	len = ft_strlen(s);
	i = -1;
	state[0] = 0;
	state[1] = 0;
	state[2] = 0;
	while (++i < len)
		if (!trim_quotes_antislash(s, i, state))
			if (!trim_quotes_simple(s, i, state))
				if (!trim_quotes_double(s, i, state))
					if (s[i] == '$' && s[i + 1] && s[i + 1] != '\'' && s[i + 1]
						!= '\"' && s[i + 1] != '\\')
						if (state[2] == 0 && state[0] == 0 &&
							(s[i + 1] == '_' || ft_isalpha(s[i + 1]) ||
							ft_isdigit(s[i + 1]) || s[i + 1] == '?'))
							substitute_variable(&s, &i, &len, envar);
	if (!(new = NULL) && (state[0] || state[1] || state[2]))
		handle_error("error: multiline commands are not supported");
	new = trim_quotes_final(len, s);
	return (new);
}
