/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:56:37 by hberger           #+#    #+#             */
/*   Updated: 2019/10/16 18:17:29 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t i;

	if (ft_strlen(to_find) == 0)
		return ((char *)str);
	i = -1;
	while (++i < len)
		if (ft_strncmp((char *)&str[i], (char *)to_find,
			ft_strlen(to_find)) == 0)
		{
			if (i + ft_strlen(to_find) > len)
				return (NULL);
			return ((char *)&str[i]);
		}
	return (NULL);
}
