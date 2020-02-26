/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macasubo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:44:02 by macasubo          #+#    #+#             */
/*   Updated: 2020/02/25 23:27:34 by macasubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../libft.h"

static int	is_in_set(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		len;
	char	*result;

	len = (int)ft_strlen(s1);
	start = 0;
	end = len - 1;
	while (is_in_set(s1[start], set))
		start++;
	while (end >= 0 && is_in_set(s1[end], set))
		end--;
	if (end < start)
	{
		if (!(result = (ft_calloc(1, sizeof(char)))))
			return (NULL);
	}
	else
	{
		if (!(result = (malloc(sizeof(char) * (end - start + 2)))))
			return (NULL);
	}
	ft_strlcpy(result, &s1[start], end - start + 2);
	return (result);
}
