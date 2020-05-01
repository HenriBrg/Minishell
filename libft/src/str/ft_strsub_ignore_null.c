/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub_ignore_null.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macasubo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 14:56:57 by macasubo          #+#    #+#             */
/*   Updated: 2020/05/01 15:50:49 by macasubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char		*ft_strsub_ignore_null(char const *s,
				unsigned int start, size_t len)
{
	char	*output;
	int		real_len;
	int		i;

	if (s == 0)
		return (0);
	real_len = 0;
	i = start - 1;
	while (++i < (int)len)
		if (s[i])
			real_len++;
	if (!(output = (char *)malloc(sizeof(char) * (real_len + 1))))
		return (0);
	i = start - 1;
	real_len = 0;
	while (++i < (int)len)
	{
		if (s[i])
		{
			output[real_len] = s[i];
			real_len++;
		}
	}
	output[real_len] = 0;
	return (output);
}
