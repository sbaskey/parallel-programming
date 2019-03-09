// c program to compute the series 4*(1-1/(2*n + 1)) using mutex
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
//mutex initialized
pthread_mutex_t lock;
double sum=0;  //global sum
long long iters=0; //no of iterators
int Num_threads;  //no of threads
int flag=0;
void *compute_sum(void *rank); //compute_sum function defined
int main(int argc,char *argv[])
{
   if (argc==1)
   {
     printf("insufficient arguments\n");
     exit(1);
   }
    pthread_t thread[100];
    double val=0.0;
    long i;
    //no of iterators read
   iters = strtoll(argv[1], NULL, 10); 
   //no of threads read 
    Num_threads= strtoll(argv[2], NULL, 10);  

    //clock initialized
    clock_t t; 
    t = clock(); 

    //thread created and are made to compute sum
    for(  i=0; i<Num_threads; i++)
      pthread_create(&thread[i], NULL,compute_sum,(void*)i); 

    //main function waits all threads to complete their task
    for(  i= 0; i<Num_threads; i++) 
    pthread_join(thread[i], NULL);
    val =4*sum;

  //time is calculated
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
    //global sum is updated using mutex
    pthread_mutex_lock(&lock);
  	sum += factor/(double) (2*i+1);
  	factor = -1.0 * factor;
    pthread_mutex_unlock(&lock);
    
  }			
  return NULL;
}