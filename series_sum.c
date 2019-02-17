#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>   
#include <pthread.h> 
float s1=0;
float s2=0;
int n=1000;
int i=0;
int j;
//j=n/2;
void *sum1(void *vargp) 
{ 
    while(i<n/2)
        {
            if(i%2==0)
             s1+=1./(2*i+1);
             else
             s1-=1./(2*i+1);
            i++;
        }
    return NULL;
} 
void *sum2(void *vargp) 
{ 
    j=n/2;
   while( j<n)
   {
       if(j%2==0)
       s2+=1./(2*j+1);
       else
       s2-=1./(2*j+1);
       j++;
   }
    return NULL; 
} 
   
int main() 
{    j=n/2;
    pthread_t t1; 
    pthread_t t2;
    
   
    pthread_create(&t1, NULL, sum1, NULL); 
    pthread_create(&t2, NULL, sum2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2,NULL); 
    printf("sum=%f\n",4*(s1+s2));
    return 0;
}