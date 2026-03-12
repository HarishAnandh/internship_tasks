#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#define BUFFER_SIZE 2
#define ITEMS 4
sem_t full,empty,mutex;
int buffer[BUFFER_SIZE];
int in = 0,out = 0;
void *producer(void *arg){
    for(int i = 1;i<=ITEMS;i++){
         sem_wait(&empty);
         sem_wait(&mutex);
         buffer[in] = i;
         
         printf("produced index %d in %d\n",i,in);
         in = (in+1)%BUFFER_SIZE;
         sem_post(&mutex);
         sem_post(&full);
         sleep(1);
         }
         return NULL;
         }
 void *consumer(void *arg){
     for(int i = 1;i<=ITEMS;i++){
         sem_wait(&full);
         sem_wait(&mutex);
         int item = buffer[out];
         
         printf(" consumed index %d in %d\n",i,out);
         out = (out+1)%BUFFER_SIZE;
         sem_post(&mutex);
         sem_post(&empty);
         sleep(1);
         }
         return NULL;
         }
     int main(){
          pthread_t t1,t2;
          sem_init(&empty,0,BUFFER_SIZE);
          sem_init(&full,0,0);
          sem_init(&mutex,0,1);
          pthread_create(&t1,NULL,producer,NULL);
          pthread_create(&t2,NULL,consumer,NULL);
          pthread_join(t1,NULL);
          pthread_join(t2,NULL);
          sem_destroy(&empty);
          sem_destroy(&full);
          sem_destroy(&mutex);
          return 0;
          }
          
