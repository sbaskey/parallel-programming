//barrier using condtional wait
// c program to compute the series 4*(1-1/(2*n + 1)) using barrier(barrier using conditional variable)
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
int counter=0;  //global counter     
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER; //mutex initialized
pthread_cond_t cond_var=PTHREAD_COND_INITIALIZER; //conditional variable initialised
double sum=0; //global sum
long long iters=0;
int Num_threads;
int flag=0;
void *compute_sum(void *rank);
int main(int argc,char *argv[])
{
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
    //clock initialised
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
    //time calculated
  t = clock() - t; 
  double time_taken = ((double)t)/CLOCKS_PER_SEC;

  //iters,no of threads,val and time is returned
 printf("%lld %d %.2f %f\n", iters,Num_threads,val,time_taken);
  return 0;
}
void *compute_sum(void *rank) 
{
  //partition of iterators is done
  long my_rank = (long) rank;
  double factor;
  long long i;
  long long my_n = iters/Num_threads;
  long long my_first_i = my_n * my_rank;
  long long my_last_i = my_first_i + my_n;
  long long my_sum=0;
  if(my_first_i%2==0)
    factor=1.0;
else
    factor=-1.0;
  for (i = my_first_i; i < my_last_i; i++) 
  {
    //global sum is update using barrier
    //barrier
  pthread_mutex_lock(&mutex);
  sum+=factor/(double) (2*i+1);
  factor = -1.0 * factor;
  //wake up all thread if counter==no of threads
  if (counter==Num_threads-1) 
  {
    counter=0;
    pthread_cond_broadcast(&cond_var); //wake up all
  }
  else 
     {
     counter++;
     pthread_cond_wait(&cond_var, &mutex); //wait till counter==no of thread
     }

  pthread_mutex_unlock(&mutex);
  
  }			
  return NULL;
}