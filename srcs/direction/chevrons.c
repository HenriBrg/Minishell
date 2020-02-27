/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevrons.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 19:55:57 by hberger           #+#    #+#             */
/*   Updated: 2020/02/27 20:21:36 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*

typedef struct				s_strlist
{
	char					*str;
	int						out_type;
	struct s_strlist		*next;
}							t_strlist;
​
typedef struct				s_command
{
	char					**args;
	t_strlist				*out;
	t_strlist				*in;
}

*/

int		nopiped_chevrons(t_command *tab, t_envar *envar)
{
	t_strlist			*tmp;
	(void)envar;

	tmp = tab[0].out;
	while (tmp)
	{
		int fd = open(tmp->str, O_CREAT | O_WRONLY | O_TRUNC, 0777);// (tmp->out_type == 2 ? O_APPEND : O_TRUNC), 0777);
		if (tmp->next == 0 && fd != -1)
		{
			printf("DUP\n");
			dup2(fd, STDOUT_FILENO);
			close(fd);
			return 0;
		}
		tmp = tmp->next;
	}

	// tmp = tab[0].in;
	// while (tmp)
	// {
	// 	printf("in\n");
	// 	fd = open(tmp->str, O_RDONLY, 0777);
	// 	// if (tmp->net == 0 && fd != -1)
	// 	// 	dup2(fd, 0);
	// 	tmp = tmp->next;
	// }
	return (0);
}

/*
int		nopiped_chevrons(t_command *tab, t_envar *envar)
{
	int					pid;
	int					fd;
	t_strlist			*tmp;



	(void)envar;
	(void)fd;

	tmp = tab[0].out;
	if ((pid = fork()) < 0)
		exit((g_exitvalue = EXIT_FAILURE));
	else if (pid == 0)
	{
	    // if (in)
	    // {
	    //     int fd0 = open(input, O_RDONLY);
	    //     dup2(fd0, STDIN_FILENO);
	    //     close(fd0);
	    // }

		// tmp = tab[0].out;
		// while (tmp)
		// {
		// 	int fd1 = open(tmp->str, O_CREAT | O_WRONLY | O_TRUNC, 0777);// (tmp->out_type == 2 ? O_APPEND : O_TRUNC), 0777);
		// 	if (tmp->next == 0 && fd != -1)
		// 		dup2(fd1, STDOUT_FILENO);
	    //     close(fd1);
		// 	tmp = tmp->next;
		// }

	    if (tmp)
	    {
			int fd1 = open(tmp->str, O_CREAT | O_WRONLY | O_TRUNC, 0777);// (tmp->out_type == 2 ? O_APPEND : O_TRUNC), 0777);
	        dup2(fd1, STDOUT_FILENO);
	        close(fd1);
	    }

		if (isbuiltin(tab->args))
		{
			printf("buitin\n");
			executebuiltins(tab->args, envar);
			exit(0);
		}
		else
			executablesnofork(tab->args, envar);
	}
	else
	{
		wait(NULL);
	}
	return 0;

}
*/



/**
 * Executes the command "grep Villanova < scores > out".
 *
 * @author Jim Glenn
 * @version 0.1 9/23/2004
 */

// int main(int argc, char **argv)
// {
//   int in, out;
//   char *grep_args[] = {"grep", "Villanova", NULL};
//
//   // open input and output files
//
//   in = open("scores", O_RDONLY);
//   out = open("out", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
//
//   // replace standard input with input file
//
//   dup2(in, 0);
//
//   // replace standard output with output file
//
//   dup2(out, 1);
//
//   // close unused file descriptors
//
//   close(in);
//   close(out);
//
//   // execute grep
//
//   execvp("grep", grep_args);
// }
