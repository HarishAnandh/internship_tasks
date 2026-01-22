#include<iostream>
using namespace std;
float TPT(float n,float t){
  
     return n/t;
     }
float TAT(float c,float a){
  
    return c-a;
    }
float WT(float t,float b){
   
    return t-b;
    }


int main(){
   float x,y,z;
   int n;
   cin>>n;
   int sum = 0;
   int b[n];
   int a[n];
   for(int i =0;i<n;i++){
   cout<<"insert AT:"<<endl;
   cin>>x;
   a[i] = x;
   cout<<"insert BT:"<<endl;
   cin>>y;
   b[i] = y;
   sum += y;
   }
   float tpt = TPT(n,sum);
   cout<<"tpt = "<<tpt<<endl;
   float tat= 0;
   float wt;
   float t[n];
   for(int i =0;i<n;i++){
   if( i > 0){
     tat+= TAT(b[i] + b[i-1],a[i]);
     t[i] = TAT(b[i] + b[i-1],a[i]);
     wt = WT(t[i],b[i]);
}
    else {
     tat+= TAT(b[i],a[i]);
     t[i] = TAT(b[i] ,a[i]);
     wt = WT(t[i],b[i]);
     }
     cout <<"tat : "<< tat<< "--- wt : " <<wt<<endl;
     }
     return 0;
     }
     
    
    
   
   
   
   
