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
		printf("1- CALL PIPE() and FORK()\n");
		if ((pid = fork()) == -1) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0) { // On est dans le processus fils
			printf("3- DUP FDD FROM CHILD - Then DUP2 & EXCV\n");
			dup2(fdd, 0); // Au premier tout cela ne change rien
			if (*(cmd + 1) != NULL) {
				printf("CMD + 1 EXISTS\n");
				dup2(fd[1], 1);
			}
			close(fd[0]);
			execv((*cmd)[0], *cmd);
			exit(1);
		}
		else {
			printf("2- WAIT CHILD FROM PARENT\n");


			
			wait(NULL); 		/* Collect childs */
			close(fd[1]);
			printf("4- OLD FDD : %d\n", fdd);
			fdd = fd[0];
			printf("5- NEW FDD : %d\n", fdd);
			cmd++;
		}
		printf("\n\n\n1 LOOP DONE \n\n\n");
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
	char *ls[] = {"/bin/ls", NULL};
	char *rev[] = {"/usr/bin/rev", NULL};
	char *nl[] = {"/usr/bin/nl", NULL};
	char *cat[] = {"/bin/cat", "-e", NULL};
	char **cmd[] = {ls, wc, nl, NULL};
	// char *c1[] = {"cat", "/dev/urandom"};
	// char *c2[] = {"head", "-c", "1000"};
	// char *c3[] = {"wc", "-c"};
	// char **mycmd[] = {c1, c2, c3, NULL};

	pipeline(cmd);
	return (0);
}
