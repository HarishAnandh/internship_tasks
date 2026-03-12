#include<stdio.h>
int g = 0;
void foo(int x){
  int y = g * x;
  printf("%d\n",y);
  }
int main(){
   int a = 5;
   foo(a);
   return 0;
   }
