/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:56:32 by hberger           #+#    #+#             */
/*   Updated: 2020/03/04 22:45:54 by macasubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void		handle_error(char *message)
{
	if (message)
		ft_putendl_fd(message, 2);
	else
		ft_putendl_fd(strerror(errno), 2);
	g_exitvalue = EXIT_FAILURE;
	exit(EXIT_FAILURE);
}
