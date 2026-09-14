/**
 * ============================================================
 * HW3: Synchronization — Deadlock
 * ============================================================
 *
 * This program creates two threads and two mutexes.
 *
 * Each thread acquires the mutexes in a different order.
 * This can cause a deadlock.
 *
 * First, run the provided program and observe its behavior.
 *
 * Then, modify the locking order so that the deadlock is
 * prevented.
 *
 * TODO:
 *   1. Run the program and observe where it stops.
 *
 *   2. Identify which mutex each thread holds.
 *
 *   3. Identify which mutex each thread is waiting for.
 *
 *   4. Modify the mutex acquisition order so that both
 *      threads acquire the mutexes in the same order.
 *
 *   5. Run the modified program and verify that both threads
 *      finish successfully.
 *
 * See README.md for the full HW3 instructions.
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;


void *thread1_func(void *arg)
{
    (void)arg;

    pthread_mutex_lock(&mutex1);
    printf("Thread 1 acquired mutex1\n");

    /*
     * Give Thread 2 time to acquire mutex2.
     */
    sleep(1);

    printf("Thread 1 waiting for mutex2\n");
    pthread_mutex_lock(&mutex2);

    printf("Thread 1 acquired mutex2\n");

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    return NULL;
}


void *thread2_func(void *arg)
{
    (void)arg;

    pthread_mutex_lock(&mutex2);
    printf("Thread 2 acquired mutex2\n");

    /*
     * Give Thread 1 time to acquire mutex1.
     */
    sleep(1);

    printf("Thread 2 waiting for mutex1\n");
    pthread_mutex_lock(&mutex1);

    printf("Thread 2 acquired mutex1\n");

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    return NULL;
}


int main()
{
    pthread_t thread1;
    pthread_t thread2;

    pthread_create(
        &thread1,
        NULL,
        thread1_func,
        NULL
    );

    pthread_create(
        &thread2,
        NULL,
        thread2_func,
        NULL
    );

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both threads finished.\n");

    return 0;
}