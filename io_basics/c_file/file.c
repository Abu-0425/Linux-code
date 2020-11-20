#include <stdio.h>
#include <string.h>

int main()
{
  //以w+的方式打开当前目录下的文件”linux“
  FILE *fp = fopen("./liunx","w+");
  if(fp == NULL) {
    perror("fopen");
    return -1;
  }

  printf("open sucess!\n");
  char buf[1024] = {0};
  strcpy(buf, "Linux is cool");
  //将buf中的内容写入到该文件中
  size_t w_ret = fwrite(buf, 1, strlen(buf), fp);
  printf("w_ret = %d\n", w_ret);

  //清空buf中的内容
  memset(buf, 0 ,sizeof(buf));
  //使文件流指针偏移到文件头部
  fseek(fp, 0, SEEK_SET);

  //将文件中的内容读至buf中
  size_t r_ret = fread(buf, 1, sizeof(buf)-1, fp);
  printf("r_ret = %d\n", r_ret);
  printf("buf : %s\n", buf);

  //关闭文件流指针
  fclose(fp);

  return 0;
}
