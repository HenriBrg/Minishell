/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevrons.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 19:55:57 by hberger           #+#    #+#             */
/*   Updated: 2020/02/26 21:41:48 by hberger          ###   ########.fr       */
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


*/

void		nopiped_chevrons(t_command *tab, t_envar *envar)
{
	int 				in;
	int 				out;
	struct t_strlist	*tmp;

	tmp = tab[0].in;
	while (tmp)
	{
		dup2(fd, 1);
		tmp = tmp->in->next;
	}

	tmp = tab[0].out;
	while (tmp)
	{
		dup2(fd, 1);
		tmp = tmp->next;
	}

}




/**
 * Executes the command "grep Villanova < scores > out".
 *
 * @author Jim Glenn
 * @version 0.1 9/23/2004
 */

int main(int argc, char **argv)
{
  int in, out;
  char *grep_args[] = {"grep", "Villanova", NULL};

  // open input and output files

  in = open("scores", O_RDONLY);
  out = open("out", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

  // replace standard input with input file

  dup2(in, 0);

  // replace standard output with output file

  dup2(out, 1);

  // close unused file descriptors

  close(in);
  close(out);

  // execute grep

  execvp("grep", grep_args);
}
