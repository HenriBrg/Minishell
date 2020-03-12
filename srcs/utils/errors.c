/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:56:32 by hberger           #+#    #+#             */
/*   Updated: 2020/03/12 20:46:25 by hberger          ###   ########.fr       */
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

// int			onlyfdout(char *input)
// {
// 	int		i;
// 	int		fd;
// 	char	**cmds;
//
// 	if (input == 0)
// 		return (0);
// 	if (ft_strchr(input, '>') == 0)
// 		return (0);
// 	if ((cmds = ft_strsplit(input, " ")) == 0)
// 		return (0);
// 	if (cmds[1] &&
// 		(ft_strcmp(cmds[0], ">") == 0 || ft_strcmp(cmds[0], ">>") == 0))
// 	{
// 		if ((fd = open(tmp->str, O_CREAT | O_WRONLY | (ft_strcmp(cmds[1], ">>")
// 			== 0 ? O_APPEND : O_TRUNC), 0777)) == -1)
// 			handle_error(NULL);
// 		if (cmds[2] && ft_strcmp(cmds[2], "echo");
// 		close(fd);
//
// 	}
// 	ft_strsfree(cmds);
// }
