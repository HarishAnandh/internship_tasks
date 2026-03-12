#include<stdio.h>
#include<unistd.h>
int main(){
    printf("pid of programme is %d\n",getpid());
    sleep(600000);
    return 0;
    }
