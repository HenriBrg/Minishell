/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 00:00:15 by hberger           #+#    #+#             */
/*   Updated: 2019/12/19 18:05:54 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int		check(char *charset, char c)
{
	int i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (charset[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int		words(char *str, char *charset)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (str[i] != '\0')
	{
		if (check(charset, str[i]))
		{
			x++;
			while (str[i] != '\0' && check(charset, str[i]))
				i++;
		}
		else
			i++;
	}
	return (x + 1);
}

char	*copy(char *str, char *charset)
{
	int		i;
	char	*output;

	i = 0;
	while (str[i] != '\0' && check(charset, str[i]))
		i++;
	if ((output = (char*)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	i = 0;
	output[i] = '\0';
	while (str[i] != '\0')
		if (check(charset, str[i]))
		{
			while (str[i] != '\0' && check(charset, str[i]))
			{
				output[i] = str[i];
				i++;
			}
			output[i] = '\0';
			return (output);
		}
		else
			i++;
	return (0);
}

char	**ft_strsplit(char *str, char *charset)
{
	int		i;
	int		x;
	char	**result;

	if (*charset == '\0' || charset == 0)
		return (0);
	if ((result = malloc(sizeof(char*) * words(str, charset))) == NULL)
		return (NULL);
	i = 0;
	x = 0;
	while (str[i] != '\0')
	{
		if (check(charset, str[i]))
		{
			result[x] = copy(str + i, charset);
			while (str[i] != '\0' && check(charset, str[i]))
				i++;
			x++;
		}
		else
			i++;
	}
	result[x] = 0;
	return (result);
}
