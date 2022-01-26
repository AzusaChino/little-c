#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    // fork a child process
    pid = fork();

    if (pid < 0)
    {
        perror("fork error");
        exit(1);
    }
    // enter child process block
    if (pid == 0)
    {
        printf("Inside child process!\n");
        printf("pid = %d, ppid = %d\n", getpid(), getppid());
        sleep(5);
        printf("\n pid = %d, ppid = %d\n", getpid(), getppid());
    }
    else
    {
        // enter parent process
        printf("Inside parent process!\n");
        sleep(1);
        printf("parent process exited!\n");
    }
    return 0;
}