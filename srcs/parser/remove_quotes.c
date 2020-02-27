/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_supersplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macasubo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 01:44:19 by macasubo          #+#    #+#             */
/*   Updated: 2020/02/26 18:54:54 by macasubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char			*trim_quotes(char *s)
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
