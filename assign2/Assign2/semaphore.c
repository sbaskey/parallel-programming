#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
//semaphore initialized
sem_t mutex;
//global sum
double sum=0;
//no of iterators
long long iters=0;
//no of threads
int Num_threads;
int flag=0;
//compute_sum function defined
void *compute_sum(void *rank);
int main(int argc,char *argv[])
{
    sem_init(&mutex,0,1);
    pthread_t thread[100];
    double val=0.0;
    long i;

    if (argc==1)
   {
     printf("insufficient arguments\n");
     exit(1);
   }
   //no of iterators read
   iters = strtoll(argv[1], NULL, 10);
    //no of threads read 
   Num_threads= strtoll(argv[2], NULL, 10);

//clock clock started
    clock_t t; 
    t = clock(); 


  //thread created and are made to compute sum
    for(  i=0; i<Num_threads; i++)
      pthread_create(&thread[i], NULL,compute_sum,(void*)i); 

  //main function waits all threads to complete their task
    for(  i= 0; i<Num_threads; i++) 
    pthread_join(thread[i], NULL);

    //global sum finalized
    val =4*sum;

    //semphore destroyed
    sem_destroy(&mutex);

   //time calculated
  t = clock() - t; 
  double time_taken = ((double)t)/CLOCKS_PER_SEC;

  //iters,no of threads,val and time is returned
  printf("%lld %d %.2f %f\n", iters,Num_threads,val,time_taken);
  return 0;
}
void *compute_sum(void *rank) 
{
  //partion of iterators is done
  long my_rank = (long) rank;
  double factor;
  long long i;
  long long my_n = iters/Num_threads;
  long long my_first_i = my_n * my_rank;
  long long my_last_i = my_first_i + my_n;
  long long my_sum;
  
  if(my_first_i%2==0)
    factor=1.0;
else
    factor=-1.0;
  for (i = my_first_i; i < my_last_i; i++) 
{
    //global sum is updated using semaphore
    sem_wait(&mutex);
  	sum += factor/(double) (2*i+1);
  	factor = -1.0 * factor;
    sem_post(&mutex);
    
  }			
  return NULL;
}