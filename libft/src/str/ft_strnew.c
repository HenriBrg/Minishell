/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:14:31 by hberger           #+#    #+#             */
/*   Updated: 2019/10/16 18:30:03 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strnew(size_t size)
{
	char	*output;

	if ((output = (char*)malloc((size + 1) * sizeof(char))) == NULL)
		return (NULL);
	ft_memset(output, '\0', size + 1);
	return (output);
}
