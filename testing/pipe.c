/*
** http://debian-facile.org/doc:programmation:shell:pipe
** a taille d'un tube est bien sûr limitée. Elle a pour valeur 4096 en général (constante PIPE_BUF de <limits.h>).
** S'il arrive que le nombre de caractères à écrire soit supérieur à cette limite,
** le message peut être écrit mais décomposé par le système en plusieurs lots. L'atomicité serait alors perdue.
**
** LIENS UTILES
** https://www.emi.ac.ma/ntounsi/COURS/C/Pipe/pipe.html
** http://debian-facile.org/doc:programmation:shell:pipe
** Le mieux : http://www.zeitoun.net/articles/communication-par-tuyau/start et https://n-pn.fr/t/2318-c--programmation-systeme-execve-fork-et-pipe
*/

/*
** pipex.c - multipipes support
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
 * loop over commands by sharing
 * pipes.
 */

static void
pipeline(char ***cmd)
{
	int fd[2];
	pid_t pid;
	int fdd = 0;				/* Backup */

	while (*cmd != NULL) {
		pipe(fd);
		if ((pid = fork()) == -1) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0) {
			dup2(fdd, 0);
			if (*(cmd + 1) != NULL) {
				dup2(fd[1], 1);
			}
			close(fd[0]);
			execv((*cmd)[0], *cmd);
			exit(1);
		}
		else {
			wait(NULL); 		/* Collect childs */
			close(fd[1]);
			fdd = fd[0];
			cmd++;
		}
	}
}

/*
 * Compute multi-pipeline based
 * on a command list.
 */
int
main(int argc, char *argv[])
{
	char *wc[] = {"/usr/bin/wc", NULL};
	char *ls[] = {"/bin/ls", "-al", NULL};
	char *rev[] = {"/usr/bin/rev", NULL};
	char *nl[] = {"/usr/bin/nl", NULL};
	char *cat[] = {"/bin/cat", "-e", NULL};
	char **cmd[] = {ls, NULL};

	pipeline(cmd);
	return (0);
}
