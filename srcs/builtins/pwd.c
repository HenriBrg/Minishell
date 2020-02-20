/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 00:31:17 by hberger           #+#    #+#             */
/*   Updated: 2020/02/21 00:31:23 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void		builtinpwd(t_envar *envar)
{
	char	*tmp;

	tmp = getvar(envar, "PWD");
	if (tmp)
		ft_putendl_fd(tmp, 1);
		// REMEMBER $?
	else
		return ;
		// REMEMBER $?
}
