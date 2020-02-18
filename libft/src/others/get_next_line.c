/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:08:42 by hberger           #+#    #+#             */
/*   Updated: 2019/10/28 19:00:09 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static char	*ft_read(const int fd, char *str)
{
	int		x;
	char	*tmp;
	char	buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, buffer, 0) < 0)
		return (0);
	str = (str == 0) ? ft_strnew(1) : str;
	while (ft_strchr(str, '\n') == 0)
	{
		tmp = str;
		if ((x = read(fd, buffer, BUFFER_SIZE)) < 0)
			return (0);
		buffer[x] = '\0';
		str = ft_strjoin(str, buffer);
		free(tmp);
		if (x == 0 || str[0] == '\0')
			break ;
	}
	return (str);
}

int			get_next_line(int fd, char **line)
{
	int				i;
	char			*tmp;
	static char		*str;

	if ((str = ft_read(fd, str)) == 0)
		return (-1);
	if (((tmp = ft_strchr(str, '\n')) > 0))
	{
		i = tmp - str;
		tmp = ft_strdup(str + i + 1);
		if ((*line = ft_strndup(str, i)) == 0)
			return (-1);
		free(str);
		str = ft_strdup(tmp);
		free(tmp);
		return (1);
	}
	else
	{
		if ((*line = ft_strdup(str)) == 0)
			return (-1);
		free(str);
		str = NULL;
		return (0);
	}
}
