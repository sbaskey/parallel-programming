// c program to compute the series 4*(1-1/(2*n + 1)) using busy_wait

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
double sum=0;//glaobla sum
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

    //clock started
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
  long my_rank = (long) rank;
  //printf("%ld",my_rank);
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
    while (flag != my_rank);
  	sum += factor/(double) (2*i+1);
  	factor = -1.0 * factor;
    flag = (flag+1) % Num_threads; 
  }			
  return NULL;
}