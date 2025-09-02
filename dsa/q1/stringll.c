#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct noderec{
  char name[80];
  int age;
  struct noderec *next;
};
typedef struct noderec *node;
node temp,new1,prev;
typedef node header;
header h;
void create(){
    h = (struct noderec*)malloc(sizeof(struct noderec));
    h->next = h;
}
int isEmpty(header h){
    return (h->next == h);
}
void insertBeg(char *a,int x){
    new1 = (struct noderec*)malloc(sizeof(struct noderec));
    strcpy(new1->name,a);
    new1->age = x;
    new1->next = h->next;
    h->next = new1;
}
void deletebyname(char *a){
    if(!isEmpty(h)){
    temp = h->next;
    prev = temp;
    while(temp != h && strcmp(temp->name,a) != 0){
        prev = temp;
        temp = temp->next;
    }
    prev->next = temp->next;
       free(temp);
    }
    
}
void display(){
    temp = h->next;
    while(temp != h){
        printf("[%s, ", temp->name);
        printf("%d] ->", temp->age);
        temp = temp->next;
    }
}
int main(){
    int x,y;
    create();
    scanf("%d",&x);
    int i=0;
    while(i<x){
    scanf("%d",&y);
    switch(y){
        case 1:
        int a;
        char n[20];
        scanf("%s",n);
        scanf("%d",&a);
        insertBeg(n,a);
        display();
        break;
        case 2:
        char o[20];
        scanf("%s",o);
        deletebyname(o);
        display();
        break;
        
    }
        
     i++;   
    }
    return 0;
}

