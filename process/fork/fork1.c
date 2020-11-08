#include <stdio.h>
#include <unistd.h>

//父子进程代码共享，但数据独有
int g_val = 100;
int main()
{
    pid_t pid = fork();//创建子进程
    if(pid < 0) {
        printf("fork error!\n");
    }
    else if(pid == 0) {
        //子进程
        g_val = 200;
        printf("This is Child! g_val = %d p = %p\n",g_val,&g_val);
    }
    else {
        //父进程
        sleep(1);
        printf("This is Parent! g_val = %d p = %p\n",g_val,&g_val);
    }
    return 0;
}
