#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define ARRAY_SIZE 5000
#define NUM_OF_THREADS 5

int arr[ARRAY_SIZE];
int global_index = 0;
int sum = 0;
pthread_mutex_t mutex;

void *voila(void *nothing)
  { long tid = (long)nothing,
         begin = (tid-1) * 1000,
         end = (tid *1000 - 1);
    int localSum = 0;
    do {
        pthread_mutex_lock(&mutex);
        // set local_index to the updated global_index and 
        //increment global index after, move through array
        
        sum = sum + arr[begin++];
        pthread_mutex_unlock(&mutex);

       
        //printf("\n%d\n",partial_sum);
    } while(begin <= end);

    pthread_mutex_lock(&mutex);
    sum += localSum;
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char*argv[])
{
    pthread_t threads[NUM_OF_THREADS];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < ARRAY_SIZE; i++)
        arr[i] = i+1;

    for (long int i = 1; i <= NUM_OF_THREADS ; i++){
        pthread_create(&threads[i] , NULL, voila, (void *)i);
        //printf("Finishing thread = %ld\n",i);
    }
    for (int i = 1; i <= NUM_OF_THREADS; i++)
        pthread_join(threads[i] , NULL);

    printf("The sum of 1 to %d is %d\n", ARRAY_SIZE, sum);
    exit(0);
}
