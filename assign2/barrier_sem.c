#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
int counter;       // Initialize to 0
sem_t count_sem;   // Initialize to 1
sem_t barrier_sem; // Initialize to 0
double sum=0;
long long iters=0;
int Num_threads;
int flag=0;
void *compute_sum(void *rank);
int main()
{
    pthread_t thread[100];
    double val=0.0;
    long i;

    printf("enter the value of iterater\n");
    scanf("%lld",&iters);
    printf("enter the number of threads\n");
    scanf("%d",&Num_threads);
    clock_t t; 
    t = clock(); 
    for(  i=0; i<Num_threads; i++)
      pthread_create(&thread[i], NULL,compute_sum,(void*)i); 
    for(  i= 0; i<Num_threads; i++) 
    pthread_join(thread[i], NULL);
    val =4*sum;
  t = clock() - t; 
  double time_taken = ((double)t)/CLOCKS_PER_SEC;
  printf("time taken for execution=%f \n", time_taken); 
  printf("iters: %lld val: %.2lf\n", iters, val);
  return 0;
}
void *compute_sum(void *rank) 
{
  long my_rank = (long) rank;
  printf("%ld",my_rank);
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
  sum+=factor/(double) (2*i+1);
  factor = -1.0 * factor;
  //barrier
  sem_wait(&count_sem);
  if (counter == Num_threads-2) {
    counter=0;
    sem_post (&count_sem);
    for (int j=0; j < Num_threads - 1; j++) {
      sem_post (&barrier_sem);
    }
  }
  else {
    counter++;
    sem_post (&count_sem);
    sem_wait (&barrier_sem);
  }
  }			
  return NULL;
}