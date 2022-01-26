#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("pid = %d\n", getpid());
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("failed to fork\n");
        return -1;
    }
    else if (pid == 0)
    {
        printf("Inside child process! pid = %d\n", getpid());
        sleep(5);
        exit(0);
    }
    else if (pid > 0)
    {
        printf("Inside parent process! pid = %d\n", getpid());
    }

    while (1)
    {
        printf("-------------pid = %d\n", getpid());
        sleep(1);
    }
    return 0;
}