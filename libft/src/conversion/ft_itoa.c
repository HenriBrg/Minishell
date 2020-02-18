/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:51:25 by hberger           #+#    #+#             */
/*   Updated: 2019/10/24 18:17:10 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_itoa(int n)
{
	int		nb;
	int		size;
	int		neg;
	char	*str;

	nb = n;
	size = 0;
	str = 0;
	if (nb == -2147483648 || nb == 0)
		return (nb == 0) ? ft_strdup("0") : ft_strdup("-2147483648");
	while (nb && ++size)
		nb = nb / 10;
	if (n < 0 && size++ && (neg = 1))
		n *= -1;
	if ((str = (char*)malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	if (neg == 1)
		str[0] = '-';
	str[size--] = '\0';
	while (n)
	{
		str[size--] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}
