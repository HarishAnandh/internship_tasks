#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
    pid_t pid = fork();
   if(pid == 0){
      printf("child is executing\n");
        printf("from pid %d\n",getpid());
      _exit(0);}
    else{
       printf("parent starts executing\n");
        printf("from pid %d\n",getpid());
        sleep(60);}
        return 0;
         }
