#define _POSIX_C_SOURCE 199309L
#include<stdio.h>
#include<time.h>
#include<pthread.h>
#define ITER 2000000000LL
void *work(void* arg){
   volatile long long i;
   for(int i = 0;i< ITER;i++);
   return NULL;
   }
int main(){
  struct timespec start,end;
  clock_gettime(CLOCK_MONOTONIC,&start);
  pthread_t t1,t2,t3,t4;
  pthread_create(&t1,NULL,work,NULL);
  pthread_create(&t2,NULL,work,NULL);
  pthread_create(&t3,NULL,work,NULL);
  pthread_create(&t4,NULL,work,NULL);
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  pthread_join(t3,NULL);
  pthread_join(t4,NULL);
  clock_gettime(CLOCK_MONOTONIC,&end);
  double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) /1e9;
  printf("Time taken %.2f seconds\n",time);
  return 0;
  }
