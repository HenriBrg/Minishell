# include <sys/types.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>

int    executables(char *str, char **av)
{
  pid_t pid;

  pid = fork();
  if (pid == 0)
		execv(str, av);
  else if (pid < 0)
		return (-1);
  wait(&pid);
  return (0);
}


int main(int ac, char **av)
{
	//executables("/usr/bin/cd", av);
	executables("/bin/ls", av)
	return 0;
}
