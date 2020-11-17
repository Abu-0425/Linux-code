#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_COUNT 4

int g_tickets = 100;
pthread_mutex_t lock;

void* myStartThread(void *arg)
{
  while(1) {
    pthread_mutex_lock(&lock);
    if(g_tickets > 0) {
      printf("I am thread %p, I get the number %d ticket!\n", pthread_self(), g_tickets);
      g_tickets--;
    }
    else {
      pthread_mutex_unlock(&lock);
      break;
    }
    pthread_mutex_unlock(&lock);
  }
  return NULL;
}

int main()
{
  pthread_t tid[THREAD_COUNT];
  //初始化互斥锁
  pthread_mutex_init(&lock, NULL);
  //创建工作线程
  for(int i = 0; i < THREAD_COUNT; i++) {
    int ret = pthread_create(&tid[i], NULL, myStartThread, NULL);
    if(ret < 0) {
      perror("pthread_create");
      return -1;
    }
  }
  //线程等待
  for(int i= 0; i < 4; i++) {
    pthread_join(tid[i], NULL);
  }
  //互斥锁的销毁
  pthread_mutex_destroy(&lock);

  return 0;
}
