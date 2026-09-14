#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2
#define ITERATIONS 1000000

int counter = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void *increment_counter(void *arg)
{
    (void)arg;

    for (int i = 0; i < ITERATIONS; i++) {

        pthread_mutex_lock(&mutex);

        counter++;

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}


int main()
{
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(
            &threads[i],
            NULL,
            increment_counter,
            NULL
        );
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter value: %d\n", counter);
    printf(
        "Expected counter value: %d\n",
        NUM_THREADS * ITERATIONS
    );

    return 0;
}