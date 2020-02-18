/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintmaxt_toa_base.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:09:06 by hberger           #+#    #+#             */
/*   Updated: 2019/10/16 18:33:20 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_uintmaxt_toa_base(char *base, uintmax_t n)
{
	unsigned int	size;
	char			*str;
	uintmax_t		nb;

	nb = n;
	if (nb == 0)
		return (ft_strdup("0"));
	size = 0;
	while (nb)
	{
		nb = nb / ft_strlen(base);
		size++;
	}
	if ((str = (char*)malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	str[size--] = '\0';
	while (n)
	{
		str[size--] = base[n % ft_strlen(base)];
		n = n / ft_strlen(base);
	}
	return (str);
}
