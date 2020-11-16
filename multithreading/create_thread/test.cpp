#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct Data{
  int data;
};

void* myStartThread(void *arg)
{
  Data *pd = (Data*)arg;
  while(1) {
    printf("I am work thread!\n");
    sleep(1);
  }

  delete pd;
  pd = NULL;
  return NULL;
}
int main()
{
  pthread_t tid;
  for(int i = 0; i < 4; i++) {
    Data *pd = new Data();
    pd->data = i;
    int ret = pthread_create(&tid, NULL, myStartThread, pd);
    if(ret < 0) {
      perror("pthread_create");
      return -1;
    }

    while(1) {
      printf("I am main thread!\n");
      sleep(1);
    }
  } 
  return 0;
}
