# include <sys/types.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>

/*
** executables() intervient lorsqu'une commande shell autre qu'un des builtins
** est demandée
** 1 - On contrôle qu'on a accès aux path avec access (aka echo $PATH)
** 2 - On ouvre un processus fils dans le quel sera exécuté avec execv()
**     la commande demandée
** 3 - Si le fork réussi, on wait la fin du processus fils (à approfondir)
*/

int    executables(char *str, char **av)
{
  pid_t pid;

  pid = fork();
  if (pid == 0)
  {
	  printf("executing...\n");
	  //printf("%s\n", av[0]);
	  execv(str, av);
  }
  else if (pid < 0)
  {
    printf("Fork Failed\n");
    return (-1);
  }
  wait(&pid);
  return (0);
}


int main(int ac, char **av)
{
	executables("/usr/bin/cd", av);
	executables("/bin/ls", av);

	return 0;
}
