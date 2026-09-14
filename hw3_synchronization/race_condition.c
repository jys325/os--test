/**
 * ============================================================
 * HW3: Synchronization — Race Condition and Mutex
 * ============================================================
 *
 * This program creates two threads that increment the same
 * shared variable, "counter".
 *
 * First, compile and run the provided program several times
 * and observe the race condition.
 *
 * Then, modify this program using a POSIX mutex so that the
 * shared counter is updated correctly.
 *
 * TODO:
 *   1. Observe the behavior of the program without synchronization.
 *
 *   2. Declare and initialize a mutex.
 *
 *   3. Identify the critical section in increment_counter().
 *
 *   4. Protect the critical section using:
 *        pthread_mutex_lock()
 *        pthread_mutex_unlock()
 *
 *   5. Run the modified program several times and compare
 *      the results with the original program.
 *
 * See README.md for the full HW3 instructions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2
#define ITERATIONS 1000000

/* Shared variable */
int counter = 0;


/*
 * Each thread executes this function.
 */
void *increment_counter(void *arg)
{
    (void)arg;

    for (int i = 0; i < ITERATIONS; i++) {

        /* TODO: Add synchronization if necessary. */
        counter++;
    }

    return NULL;
}


int main()
{
    pthread_t threads[NUM_THREADS];

    /*
     * Create threads.
     */
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(
            &threads[i],
            NULL,
            increment_counter,
            NULL
        );
    }

    /*
     * Wait for all threads to finish.
     */
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