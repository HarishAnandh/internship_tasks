#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
   pid_t pid = fork();
   if(pid == 0){
     printf("%d\n",getpid());
     sleep(10);
}
   else{
    wait(NULL);
    printf("PARENT IS executed after 10 seconds");
}
return 0;
}
