#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("fork()!\n");
    pid_t pid = fork();
    if(pid == 0) {
        printf("I'm child,pid = %d,ppid = %d\n",getpid(), getppid());
    }
    else if(pid > 0) {
        printf("I'm father,pid = %d,ppid = %d\n",getpid(), getppid());
    }
    else {
        perror("fork");
        return -1;
    }

    printf("11111\n");
    return 0;
}

