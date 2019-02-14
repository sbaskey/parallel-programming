/*Name:Surendra Baskey
Roll no:111601027*/
/*Documentation:
 program desc:this program is implementation of hare and turtle race .
 There are 4 threads god,hare,turtle and reporter in this program.they are started
 at same time after creation using mutex to update the global variables used 
 in the program.
 During the race hare is made to sleep for random period of time.
 God will ask to enter value for repositioning hare and turtle.
 reporter reports the position of hare and turtle

 the finish line for race is set as 100m.

 the program can be run from terminal using gcc "hare_turtle_race.c -lpthread"
   or "make run" command provided makefile is available for this program in the same folder.

 During execution user need to enter parameter for repositioning hare and turtle.
  */

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>   
#include <pthread.h> 
pthread_mutex_t lock;
int h=0; //hare initial position
int t=0; //turtle initial position
int finish_line=100;
int hf=0;  //flag for hare thread
int tf=0;  //flag for turtle thread
int rf=0;  //flag for reporter
int gf=0;  //flag for god
void *hare(void *vargp) 
{     hf=1;
   while(hf!=1 && tf!=1 && rf!=1 && gf!=1);//waits for other threads to ready
    while(h<finish_line && t<finish_line)    
    {
        if(h>=finish_line-20 && t<finish_line/2)
          {
            printf("hare is sleeping!\n");
             int r=rand()%20;
             sleep(r);
             printf("hare is awake!\n");
          }
      else{
        pthread_mutex_lock(&lock);
        int step_size=rand()%5+1;  //speed of hare varies between 1 and 5
        h+=step_size;
        pthread_mutex_unlock(&lock);
      }
    sleep(1);
    }
    return NULL; 
} 

void *turtle(void *vargp) 
{ 
     tf=1;
   while(hf!=1 && tf!=1 && rf!=1 && gf!=1);  //waits for other threads to ready
    while(t<finish_line && h<finish_line)
    {

        pthread_mutex_lock(&lock);
         t+=1;
        pthread_mutex_unlock(&lock);
        sleep(1);
   
    }
    return NULL; 
} 

void *reporter(void *arg){
     gf=1; 
    while(hf!=1 && tf!=1 && rf!=1 && gf!=1);//waits for other threads to ready
    
    while(t<finish_line && h<finish_line)
    {
       pthread_mutex_lock(&lock);
       printf("hare=%d turtle=%d\n",h,t);
       pthread_mutex_unlock(&lock);
       sleep(1);
    }
   printf("hare=%d\n",h);
   printf("turtle=%d\n",t);
    if(h>t)
    printf("winner is hare\n");
    else
    printf("winner is turtle\n");
    return NULL;

}

void *god(void *arg)
{
    gf=1;
    int reposition=0;
    while(hf!=1 && tf!=1 && rf!=1 && gf!=1);//waits for other threads to ready
    while(h<finish_line && t<finish_line)
    { 
        if(reposition==0 && h>=finish_line-10)
        {
            pthread_mutex_lock(&lock);
            printf("enter hare and turtle position\n");
            scanf("%d%d",&h,&t);
            pthread_mutex_unlock(&lock);
            reposition=1; 
            
        }
        sleep(1);
    }

   return NULL;
}
int main() 
{ 
    pthread_t t1; 
    pthread_t t2;
    pthread_t t3;
    pthread_t t4;
    if(pthread_mutex_init(&lock, NULL) != 0) 
    { 
        printf("\n mutex  has failed\n"); 
        return 1; 
    } 
    pthread_create(&t1, NULL, hare, NULL);
    pthread_create(&t2, NULL, turtle, NULL);
    pthread_create(&t3, NULL, reporter, NULL); 
    pthread_create(&t4, NULL, god, NULL); 
    pthread_join(t1, NULL);
    pthread_join(t2,NULL); 
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}
