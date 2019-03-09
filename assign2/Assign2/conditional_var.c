#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
//Declaration of thread condition variable 
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER; 
//declaring mutex 
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; 
double sum=0;
long long iters=0;
int Num_threads;
int flag=0;
void *compute_sum(void *rank);
int main(int argc,char *argv[])
{
     if (argc==1)
   {
     printf("insufficient arguments\n");
     exit(1);
   }
   iters = strtoll(argv[1], NULL, 10);
    Num_threads= strtoll(argv[2], NULL, 10);
    pthread_t thread[100];
    double val=0.0;
    long i;

    clock_t t; 
    t = clock(); 
    for(  i=0; i<Num_threads; i++)
      pthread_create(&thread[i], NULL,compute_sum,(void*)i); 
    for(  i= 0; i<Num_threads; i++) 
    pthread_join(thread[i], NULL);
    val =4*sum;
  t = clock() - t; 
  double time_taken = ((double)t)/CLOCKS_PER_SEC;
printf("%lld %d %.2f %f\n", iters,Num_threads,val,time_taken);
  return 0;
}
void *compute_sum(void *rank) 
{
  //partition of barrier
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
    //global sum is updated using conditional wait
    pthread_mutex_lock(&lock); 
  	sum += factor/(double) (2*i+1);
  	factor = -1.0 * factor;
    if(flag<Num_threads-1)
    {
        flag++;
        pthread_cond_wait(&cond1, &lock); //wait till all thread reach
    }
  //last threrad will wake up all
else
    pthread_cond_broadcast(&cond1); 
    // release lock 
  pthread_mutex_unlock(&lock); 
  }			
  return NULL;
}