#include <stdio.h>
#include <string.h>

int main()
{
  FILE *fp = fopen("./liunx","w+");
  if(fp == NULL) {
    perror("fopen");
    return -1;
  }

  printf("open sucess!\n");
  char buf[1024] = {0};
  strcpy(buf, "Linux is cool");
  size_t w_ret = fwrite(buf, 1, strlen(buf)+1, fp);
  printf("w_ret = %d\n", w_ret);

  memset(buf, 0 ,sizeof(buf));
  fseek(fp, 0, SEEK_SET);

  size_t r_ret = fread(buf, 1, sizeof(buf)-1, fp);
  printf("r_ret = %d\n", r_ret);
  printf("buf : %s\n", buf);

  fclose(fp);

  return 0;
}
