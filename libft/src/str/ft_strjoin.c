/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:14:00 by hberger           #+#    #+#             */
/*   Updated: 2019/10/16 18:31:14 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;

	if (s1 == 0 || s2 == 0 ||
		(s = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1))) == 0)
		return (0);
	s[0] = '\0';
	ft_strcat(s, s1);
	ft_strcat(s, s2);
	return (s);
}
