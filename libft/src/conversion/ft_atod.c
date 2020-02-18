/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:19:11 by henri             #+#    #+#             */
/*   Updated: 2019/12/19 21:25:05 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include <stdio.h>

double	ft_atod(const char *str)
{
	int		i;
	double	sign;
	double	step;
	double	left;
	double	right;

	i = 0;
	step = 1.0;
	left = 0.0;
	right = 0.0;
	while (ft_isspace(str[i]))
		i++;
	sign = (str[i] == '-') ? -1 : 1;
	i = (str[i] == '+' || str[i] == '-') ? i + 1 : i;
	while (str[i] != '\0' && ft_isdigit(str[i]))
		left = (left * 10) + (str[i++] - '0');
	if (str[i] != '.')
		return (left * sign);
	i++;
	while (str[i] != '\0' && ft_isdigit(str[i]) && (step *= 0.1))
		right += step * (str[i++] - '0');
	return ((left + right) * sign);
}
