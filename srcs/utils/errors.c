/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:56:32 by hberger           #+#    #+#             */
/*   Updated: 2020/05/02 17:15:18 by macasubo         ###   ########.fr       */
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

int			checkborderssymbol(char **cmds)
{
	if (ft_strcmp(cmds[0], "|") == 0)
	{
		ft_putstr_fd("minishell: error near unexpected token `|'\n", 2);
		exit((g_exitvalue = 258));
		ft_strsfree(cmds);
	}
	else if (ft_strcmp(cmds[0], ";") == 0)
	{
		ft_putstr_fd("minishell: error near unexpected token `;'\n", 2);
		exit((g_exitvalue = 258));
		ft_strsfree(cmds);
	}
	return (0);
}

int			onlyfdout(char *input)
{
	int		fd;
	char	**cmds;

	if (input == 0 || *input == '\0')
		return (0);
	if ((cmds = ft_strsplit(input, " ")) == 0)
		return (0);
	if (checkborderssymbol(cmds) == 0 && cmds[0] && cmds[1] &&
		(ft_strcmp(cmds[0], ">") == 0 || ft_strcmp(cmds[0], ">>") == 0))
	{
		if ((fd = open(cmds[1], O_CREAT | O_WRONLY | (ft_strcmp(cmds[1], ">>")
			== 0 ? O_APPEND : O_TRUNC), 0777)) == -1)
			handle_error(NULL);
		close(fd);
		ft_strsfree(cmds);
		return (1);
	}
	else if ((ft_strcmp(cmds[0], ">") == 0 ||
				ft_strcmp(cmds[0], ">>") == 0) && cmds[1] == 0)
	{
		ft_putstr_fd("minishell: error near unexpected token `newline'\n", 2);
		exit((g_exitvalue = 258));
	}
	ft_strsfree(cmds);
	return (0);
}

int			error_unexpected_token(char token)
{
	ft_putstr_fd("minishell: error near unexpected token `", 2);
	write(2, &token, 1);
	ft_putstr_fd("'\n", 2);
	exit((g_exitvalue = 258));
	return (0);
}
