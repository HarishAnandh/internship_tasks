#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
   pid_t pid = fork();
    if(pid == 0){
       printf("child is executing\n");
       printf("from pid = %d\n",getpid());
        sleep(60);
}
   else{
     printf("parent is executred\n");
    printf("from pid %d\n",getpid());
    // wait(NULL);
    _exit(0);
}
    return 0;
}
