#define _POSIX_C_SOURCE 199309L
#include<stdio.h>
#include<time.h>
int main(){
   struct timespec start,end;
   clock_gettime(CLOCK_MONOTONIC, &start);
   long long i;
   for(int i = 0;i<2000000000LL;i++);
   clock_gettime(CLOCK_MONOTONIC, &end);
   double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
   printf("time taken %.2f seconds\n",time);
   return 0;
   }
