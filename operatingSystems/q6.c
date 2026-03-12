#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
   pid_t pid = fork();
    if(pid == 0){
      printf("child is exec");
      printf("from pid = %d\n",getpid());
      execlp("ls","ls",NULL);
}
   else{
     printf("from parent %d\n",getpid());
      wait(NULL);
    printf("operation completed\n");
   }
   return 0;
}
