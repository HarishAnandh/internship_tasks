#include<stdio.h>
#include<stdbool.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/wait.h>
          int in = 0;
	  int out = 0;
	  int buffersize = 5;
	  int buffer[5];
	  int next_produced = 0;
	  int next_consumed = 0;
 void *work(void *arg){
     
	  
	   for(int i =0;i<buffersize;i++){
	     
	     
	     }
  //------------producing
	for(int i =0;i<20;i++){
	  while(((in+1)%buffersize) == out )
	    /*do nothing*/
	   buffer[in] = next_produced;
	   next_produced = i+1;
	   printf("Thread %d Produced = %d\n",i,next_produced);
	    in  = ((in+1)% buffersize); 
	    sleep(2);
	    }
 //------------consuming
  return NULL;
 }
 void *work1(void *arg){
          for(int i =0;i<buffersize;i++){
	     
	     
	     }
	 for(int i =0;i< 20;i++){
	  while(in == out)
	  /*do nothing*/ 
	   next_consumed = buffer[out];
	   next_consumed = i+1;
	   printf("Thread %d Consumed = %d\n",i,next_consumed);
	   out = ((out+1)%buffersize);
	   wait(NULL);
   	}
   return NULL;
      }
      
int main(){
        pthread_t t1,t2,t3,t4;
        pthread_create(&t1,NULL,work,NULL);
        pthread_create(&t2,NULL,work1,NULL);
        
        
        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
       
        
	
   return 0;
   }
