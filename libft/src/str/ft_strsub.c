/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:15:06 by hberger           #+#    #+#             */
/*   Updated: 2019/10/16 18:29:46 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*output;

	if (s == 0 || (output = (char*)malloc(sizeof(char) * (len + 1))) == 0)
		return (0);
	output = ft_memcpy(output, s + start, len);
	output[len] = '\0';
	return (output);
}
