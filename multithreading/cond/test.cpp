#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_COUNT 2

int noodle = 0; //面

pthread_mutex_t lock; //互斥锁
pthread_cond_t prod_cond;
pthread_cond_t cons_cond;

void* consStart(void *arg)
{
  while(1) {
    pthread_mutex_lock(&lock);
    while(noodle <= 0) {
      pthread_cond_wait(&cons_cond, &lock);
    }
    printf("I am %p, I eat %d\n", pthread_self(), noodle);
    noodle--;
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&prod_cond);
  }
  return NULL;
}

void* prodStart(void *arg)
{
  while(1) {
    pthread_mutex_lock(&lock);
    while(noodle > 0) {
      //放进prod的PCB等待队列
      pthread_cond_wait(&prod_cond, &lock);
    }
    noodle++;
    printf("I am %p, I make %d\n", pthread_self(), noodle);
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&cons_cond);
  }
  return NULL;
}

int main()
{
  pthread_mutex_init(&lock, NULL);
  pthread_cond_init(&prod_cond, NULL);
  pthread_cond_init(&cons_cond, NULL);
  pthread_t prod[THREAD_COUNT], cons[THREAD_COUNT];

  //线程创建
  for(int i = 0; i < THREAD_COUNT; i++) {
    int ret = pthread_create(&prod[i], NULL, prodStart, NULL);
    if(ret < 0) {
      perror("pthread_create");
      return -1;
    }
    ret = pthread_create(&cons[i], NULL, consStart, NULL);
    if(ret < 0) {
      perror("pthread_create");
      return -1;
    }
  }
  //线程等待
  for(int i = 0; i < THREAD_COUNT; i++) {
    pthread_join(prod[i], NULL);
    pthread_join(cons[i], NULL);
  }

  //销毁互斥锁及条件变量
  pthread_mutex_destroy(&lock);
  pthread_cond_destroy(&prod_cond);
  pthread_cond_destroy(&cons_cond);

  return 0;
}
