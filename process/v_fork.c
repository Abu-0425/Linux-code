#include <stdio.h>
#include <unistd.h>

int main()
{
    //pid_t pid = vfork();
    pid_t pid = fork();
    if(pid < 0) {
        printf("vfork error!\n");
        return -1;
    }
    else if(pid == 0) {
        sleep(3);
        printf("This is Child!\n");
    }
    else {
        wait(NULL);//等待子进程先退出
        printf("This is Parent!\n");
    }
    return 0;
}
