#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
   pid_t pid = fork();
   if(pid == 0){
     for(int i=0;i<3;i++){
       printf("child pid = %d,ppid = %d\n",getpid(),getppid());
      }
   }
   else{
    printf("parent pid = %d, child = %d\n",getpid(),pid);
}
 return 0;
}
