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
{
    int local_index = 0;
    int partial_sum = 0;

    do {
        pthread_mutex_lock(&mutex);
        local_index = global_index;
        global_index++;
        pthread_mutex_unlock(&mutex);

        if (local_index < ARRAY_SIZE)
            partial_sum += *(arr + local_index);
    } while(local_index < ARRAY_SIZE);

    pthread_mutex_lock(&mutex);
    sum += partial_sum;
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char*argv[])
{
    pthread_t threads[NUM_OF_THREADS];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < ARRAY_SIZE; i++)
        arr[i] = i+1;

    for (int i = 0; i < NUM_OF_THREADS ; i++)
        pthread_create(&threads[i] , NULL, voilall, NULL);

    for (int i = 0; i < NUM_OF_THREADS; i++)
        pthread_join(threads[i] , NULL);

    printf("The sum of 1 to %d is %d\n", ARRAY_SIZE, sum);
    exit(0);
}
