/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:15:00 by hberger           #+#    #+#             */
/*   Updated: 2019/10/16 18:17:35 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int i;
	int j;

	if (!to_find[0])
		return ((char*)str);
	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j] && to_find[j])
			j++;
		if (!to_find[j])
			return ((char*)&str[i]);
		i++;
	}
	return (0);
}
