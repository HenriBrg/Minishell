/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 22:10:42 by hberger           #+#    #+#             */
/*   Updated: 2019/10/24 18:16:40 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t		i;
	char		*output;

	i = 0;
	while (src[i] != '\0' && i < n)
		i++;
	if ((output = malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0' && i < n)
	{
		output[i] = src[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}
