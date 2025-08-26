#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct noderec{
char name[20];
char section[20];
char class1[20];
struct noderec *next;
};
typedef struct noderec *node;
node prev,new1,temp;
typedef node header;
header h;
header create(){
h=(struct noderec*)malloc(sizeof(struct noderec));
h->next=h;
return h;
}
int isempty(header h){
return(h->next==h);
}
void insertatbeg(header h, char *a, char *b, char *c){
new1=(struct noderec*)malloc(sizeof(struct noderec));
strcpy(new1->name, a);
strcpy(new1->section, b);
strcpy(new1->class1, c);

if(!isempty(h)){
new1->next=h->next;
h->next=new1;
}
else{
new1->next=h;
h->next=new1;
}
}
void removekid(header h,char *a){
if(!isempty(h)){
temp=h->next;
prev=temp;
while(temp!=NULL && temp->name!=a){
prev=temp;
temp=temp->next;
}
prev->next=temp->next;
free(temp);
}
}
void removekidbyp(header h,int a){
int i=1;
if(!isempty(h)){
temp=h->next;
prev=temp;
while(temp!=NULL && i!=a){
prev=temp;
temp=temp->next;
}
if(temp==NULL){
printf("the element not found");
}
else{
prev->next=temp->next;
free(temp);
}
}
}
void searchkidbyp(header h,int a){
int i=1;
if(!isempty(h)){
temp=h->next;
prev=temp;
while(temp!=NULL && i!=a){
prev=temp;
temp=temp->next;
}
if(temp==NULL){
printf("element not found");
}
else{
printf("%s",temp->name);
printf("%s",temp->class1);
printf("%s",temp->section);
}

}
}



int main(){
int a;
int i=0;
header h;
h=create();

while(i<8){
scanf("%d",&a);
switch(a){
case 1:
char n[20];
scanf("%s",n);
char o[20];
scanf("%s",o);
char j[20];
scanf("%s",j);
insertatbeg(h,n,o,j);
break;


}
i++;
}
}
