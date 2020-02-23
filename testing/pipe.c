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


//////// gcc pipe.c && ./a.out /bin/ls


#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(int argc, char *argv[], char *env[])
{
  pid_t         pid;
  int           pipe_fd[2];

  if (argc < 2)
    return 1;

  if (pipe(pipe_fd) == -1)
    {
      perror("pipe");
      return 1;
    }

  if ((pid = fork()) == -1)
    {
      perror("fork");
      return 1;
    }
  else if (pid == 0)
    {
      close(pipe_fd[0]);
      if (dup2(pipe_fd[1], 1) == -1)
      perror("dup2");
      else if (execve(argv[1], argv + 1, env) == -1)
      perror("execve");
      return 1;
    }
  else
    {
      char      buffer[1024];
      int       ret;
      int       status;

      close(pipe_fd[1]);

      while ((ret = read(pipe_fd[0], buffer, 1023)) != 0)
      {
        printf("%d\n", ret);
        buffer[ret] = 0;
        printf("%s\n", buffer);
      }
    }

  return 0;
}


// LE PIPE EN THEORIE est toujours au sein d'un fork() autrement c'est inutile

// int main()
// {
// 	int fd[2];
// 	pid_t pid;
//
// 	if (0 != pipe(fd)) {
// 	    perror("pipe");
// 	    exit(1):
// 	}
//
// 	pid = fork();
// 	if (pid == -1) {
// 	    perror("fork");
// 	    exit(0);
// 	} else if (pid == 0) {
//
// 	    /* Fils */
//
// 	    /* On ferme le cote "ecriture" du pipe */
// 	    close(fd[1]);
//
// 	    /* Maintenant on peut lire sur fd[0] */
//
// 	} else {
//
// 	    /* Pere */
//
// 	    /* On ferme le cote "lecture" du pipe" */
// 	    close(fd[0]);
//
// 	    /* Maintenant on peut ecrire sur fd[1] */
// 	}
// }
