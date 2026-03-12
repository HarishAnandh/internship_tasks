#include<stdio.h>
#include<unistd.h>
int main(){
 printf("process started\n");
 printf("pid = %d\n",getpid());
printf("sleeping ...\n");
sleep(60);
 return 0;
}
