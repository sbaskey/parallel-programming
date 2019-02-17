#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>   
#include <pthread.h> 
pthread_mutex_t lock;
int a[100000000];
int size=100000000;
int bin1=0;
int bin2=0;
int bin3=0;
void create_array(int size,int start,int end)
{  
    for(int i=0; i<size; i++)
    {
        a[i]=(rand()%(end-start+1))+start;
        //printf("%d\t",a[i]);
    }
}
void *update_bin1(void *arg)
{
    for(int i=0; i<size/4; i++){
        if(a[i]<size/4)
        {   pthread_mutex_lock(&lock);
            bin1++;
            pthread_mutex_unlock(&lock);
        }
        else if (a[i]>=size/4 && a[i]<size/2) 
        {
            pthread_mutex_lock(&lock);
            bin2++;
            pthread_mutex_unlock(&lock);
        }
        else
        {   pthread_mutex_lock(&lock);
            bin3++;
            pthread_mutex_unlock(&lock);
        }
    }  //sleep(1);
return NULL;
}
void *update_bin2(void *arg)
{
    for(int i=size/4; i<size/2; i++){
        if(a[i]<size/4)
        {   pthread_mutex_lock(&lock);
            bin1++;
            pthread_mutex_unlock(&lock);
        }
        else if (a[i]>=size/4 && a[i]<size/2) 
        {
            pthread_mutex_lock(&lock);
            bin2++;
            pthread_mutex_unlock(&lock);
        }
        else
        {   pthread_mutex_lock(&lock);
            bin3++;
            pthread_mutex_unlock(&lock);
        }
    }
return NULL;
}
void *update_bin3(void *arg)
{
    for(int i=size/2; i<size; i++){
        if(a[i]<size/4)
        {   pthread_mutex_lock(&lock);
            bin1++;
            pthread_mutex_unlock(&lock);
        }
        else if (a[i]>=size/4 && a[i]<size/2) 
        {
            pthread_mutex_lock(&lock);
            bin2++;
            pthread_mutex_unlock(&lock);
        }
        else
        {   pthread_mutex_lock(&lock);
            bin3++;
            pthread_mutex_unlock(&lock);
        }
    }
return NULL;
}

int main()
{
    pthread_t t1; 
    pthread_t t2;
    pthread_t t3;
    create_array(size,1,size);
    //update_bin();
    pthread_create(&t1, NULL, update_bin1, NULL); 
    pthread_create(&t2, NULL, update_bin2, NULL);
    pthread_create(&t3, NULL, update_bin3, NULL);  

    pthread_join(t1, NULL);
    pthread_join(t2,NULL); 
    pthread_join(t3,NULL);
    
        
printf("\n");
printf("bin1=%d\tbin2=%d\tbin3=%d",bin1,bin2,bin3);
printf("\n"); 
    
    return 0;

}