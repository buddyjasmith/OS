#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 5
#define arr_size 5000
#define start 0
int arr[arr_size];
long long int TOTAL = 0;
void *SumThread(void *threadid)
{
   long tid;
   tid = (long)threadid;
   long begin = (tid -1) * 1000,
        end = (tid*1000-1);
   printf("Starting thread #%ld with begin = %ld and end = %ld \n", tid, begin, end);
   while(begin < end){
      TOTAL = TOTAL + arr[begin++];
   }

   printf("finishing thread #%ld making you doubt your life choices with total = %lld\n", tid,TOTAL);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
   int i = start;
   for(i; i < arr_size; i++){
      arr[i]=i+1;
   }

   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   for(t=1;t<=NUM_THREADS;t++){
     printf("In main: creating thread %ld\n", t);
     rc = pthread_create(&threads[t], NULL, SumThread, (void *)t);

     if (rc){
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
       }
     }
     printf("Total in main for = %lld\n",TOTAL);

   /* Last thing that main() should do */
   exit(0);
}








