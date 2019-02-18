#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
double sum=0;
long long iters=0;
int No_threads;
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
    scanf("%d",&No_threads);

    clock_t t; 
    t = clock(); 

    for(  i=0; i<No_threads; i++)
      pthread_create(&thread[i], NULL,compute_sum,(void*)i); 
    for(  i= 0; i<No_threads; i++) 
    pthread_join(thread[i], NULL);
    val =sum;

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
  long long my_n = iters/No_threads;
  long long my_first_i = my_n * my_rank;
  long long my_last_i = my_first_i + my_n;
  long long my_sum;


  /*for (i = my_first_i+1; i<=my_last_i; i++) 
  {
    while (flag != my_rank);
    sum += i;
    //factor = -1.0 * factor;
    flag = (flag+1) % No_threads;
}
*/
for (i = my_first_i+1; i <=my_last_i; i++) {
    my_sum +=i;
    //factor = -1.0 * factor;
}

while (flag != my_rank);
sum += my_sum;
flag = (flag+1) % No_threads;
						
  return NULL;
}