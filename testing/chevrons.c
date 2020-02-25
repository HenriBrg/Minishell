#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


/*
** dup2(int fd source, int fd destination);
** Ce programme equivaut a : ls -la > ls.log
*/

int main(void)
{
    char *argv[] = { "/bin/ls", "-la", 0 };
    char *envp[] =
    {
        "HOME=/",
        "PATH=/bin:/usr/bin",
        "USER=brandon",
        0
    };
    int fd = open("ls.log", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    dup2(fd, 1); // stdout is file descriptor 1
    close(fd);
    execv(argv[0], &argv[0]);
    fprintf(stderr, "Oops!\n");
    return -1;
}
