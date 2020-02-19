# include <sys/types.h>
# include <stdio.h>

int    executables(char **cmds, char *path)
{
  pid_t pid;
  char *exec;
  struct stat s;

  exec = 0;
  if ((exec = check(cmds, &s, path, exec)) == 0)
    return (-1);
  pid = fork();
  if (pid == 0)
    execv(exec, cmds);
  else if (pid < 0)
  {
    ft_putstr("Fork Failed\n");
    return (-1);
  }
  wait(&pid);
  return (0);
}

int main()
{
	pid_t pid;
    char *exec;
    struct stat s;

	pid = fork();
	if (pid == 0)
	  execv();

}
