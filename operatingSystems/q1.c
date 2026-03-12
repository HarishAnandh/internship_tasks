#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
   pid_t pid = fork();
   if(pid == 0)
     printf("child pid = %d ; ppid = %d\n ",getpid(),getppid());
    else
     printf("parentid = %d,child = %d\n",getpid(),pid);
return 0;
}
