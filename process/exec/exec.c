#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("下面进行进程替换!\n");

    //将当前程序替换为ls程序
    execl("/usr/bin/ls","ls","-l",NULL); //l表示命令行以可变参数列表的形式给出，没有p则说明需要带路径，没有e说明不需要自己组织环境变量

    //如果进程替换成功，下面的代码将不再执行
    printf("继承替换失败!\n");

    return 0;
}
