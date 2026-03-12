#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<semaphore.h>
#include<pthread.h>
#include<time.h>
#define ITEMS 25
#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];

sem_t empty,mutex,full;

int in = 0,out =0;

void *producer(void *arg){
    for(int i =0;i<=ITEMS;i+=2){
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in] = i;
        printf("produced index = %d  value = %d\n",i,in);
        in = (in+1)%BUFFER_SIZE;
        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
        }
        return NULL;
        }
  void *consumer(void *arg){
    for(int i =0;i<=ITEMS;i+=2){
        sem_wait(&full);
        sem_wait(&mutex);
        int item= buffer[out];
        printf("consumed index = %d  value = %d\n",i,out);
        out = (out+1)%BUFFER_SIZE;
        sem_post(&mutex);
        sem_post(&empty);
        sleep(1);
        }
        return NULL;
        }
        int main(){
            pthread_t t1,t2;
            struct timespec start,end;
            clock_gettime(CLOCK_MONOTONIC,&start);
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
             clock_gettime(CLOCK_MONOTONIC,&end);
             double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1e9;
             printf("timetaken %.2f seconds\n",time);
            return 0;
            }
            
            
            
            
            
            
            
            
            
            
            
                  
  
