/**
 * ============================================================
 * HW2-3: Measure IPC Communication Time
 * ============================================================
 *
 * This program independently implements the two IPC methods from HW2-1
 * and HW2-2. Process creation and IPC setup happen before timing.
 * The measured interval is only the repeated request/response communication:
 * the parent and child exchange the same array ITERATIONS times.
 * Output and cleanup are outside the measured interval.
 *
 * Input: 100 integers (1 through 100), expected sum per iteration: 5050.
 *
 * Build & Run (Linux):
 *   gcc -O2 ipc_benchmark.c -o ipc_benchmark -pthread -lrt
 *   ./ipc_benchmark
 *
 * No code changes are required in this file. 
 *Just execute it to see the measured IPC communication time.
 */

#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <mqueue.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define ARRAY_SIZE 100
#define ITERATIONS 1000
#define RUNS 51
#define MEASURED_RUNS (RUNS - 1)

typedef struct {
    int values[ARRAY_SIZE];
    int sum;
    sem_t ready;
    sem_t done;
} SharedData;

static double clock_seconds(void) {
    struct timespec t;
    if (clock_gettime(CLOCK_MONOTONIC, &t) == -1) {
        perror("clock_gettime");
        exit(1);
    }
    return t.tv_sec + t.tv_nsec / 1e9;
}

static void wait_sem(sem_t *sem) {
    int result;
    do {
        result = sem_wait(sem);
    } while (result == -1 && errno == EINTR);
    if (result == -1) { perror("sem_wait"); exit(1); }
}

static int sum_values(const int *values) {
    int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) sum += values[i];
    return sum;
}

static double measure_shared(const int input[ARRAY_SIZE]) {
    SharedData *shared = mmap(NULL, sizeof(*shared), PROT_READ | PROT_WRITE,
                              MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared == MAP_FAILED) { perror("mmap"); exit(1); }
    if (sem_init(&shared->ready, 1, 0) == -1 || sem_init(&shared->done, 1, 0) == -1) {
        perror("sem_init"); exit(1);
    }
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); exit(1); }
    if (pid == 0) {
        for (int i = 0; i < ITERATIONS; i++) {
            wait_sem(&shared->ready);
            shared->sum = sum_values(shared->values);
            sem_post(&shared->done);
        }
        _exit(0);
    }
    double start = clock_seconds();
    for (int i = 0; i < ITERATIONS; i++) {
        memcpy(shared->values, input, sizeof(shared->values));
        sem_post(&shared->ready);
        wait_sem(&shared->done);
    }
    double elapsed = (clock_seconds() - start) * 1000;
    int status;
    waitpid(pid, &status, 0);
    int result = shared->sum;
    sem_destroy(&shared->ready); sem_destroy(&shared->done);
    munmap(shared, sizeof(*shared));
    if (result != 5050 || !WIFEXITED(status) || WEXITSTATUS(status) != 0) exit(1);
    return elapsed;
}

static double measure_message(const int input[ARRAY_SIZE]) {
    char request_name[64], response_name[64];
    snprintf(request_name, sizeof(request_name), "/hw2_bench_req_%ld", (long)getpid());
    snprintf(response_name, sizeof(response_name), "/hw2_bench_res_%ld", (long)getpid());
    struct mq_attr request_attr = {0};
    request_attr.mq_maxmsg = 2;
    request_attr.mq_msgsize = sizeof(input[0]) * ARRAY_SIZE;
    struct mq_attr response_attr = {0};
    response_attr.mq_maxmsg = 2;
    response_attr.mq_msgsize = sizeof(int);
    mqd_t request = mq_open(request_name, O_CREAT | O_RDWR, 0600, &request_attr);
    mqd_t response = mq_open(response_name, O_CREAT | O_RDWR, 0600, &response_attr);
    if (request == (mqd_t)-1 || response == (mqd_t)-1) { perror("mq_open"); exit(1); }
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); exit(1); }
    if (pid == 0) {
        int values[ARRAY_SIZE];
        for (int i = 0; i < ITERATIONS; i++) {
            if (mq_receive(request, (char *)values, sizeof(values), NULL) == -1) _exit(1);
            int sum = sum_values(values);
            if (mq_send(response, (const char *)&sum, sizeof(sum), 0) == -1) _exit(1);
        }
        _exit(0);
    }
    double start = clock_seconds();
    int result = 0;
    for (int i = 0; i < ITERATIONS; i++) {
        if (mq_send(request, (const char *)input, sizeof(int) * ARRAY_SIZE, 0) == -1) { perror("mq_send"); exit(1); }
        if (mq_receive(response, (char *)&result, sizeof(result), NULL) == -1) { perror("mq_receive"); exit(1); }
    }
    double elapsed = (clock_seconds() - start) * 1000;
    int status;
    waitpid(pid, &status, 0);
    mq_close(request); mq_close(response);
    mq_unlink(request_name); mq_unlink(response_name);
    if (result != 5050 || !WIFEXITED(status) || WEXITSTATUS(status) != 0) exit(1);
    return elapsed;
}

int main(void) {
    int input[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) input[i] = i % 100 + 1;
    double shared_total = 0.0;
    double message_total = 0.0;
    printf("IPC communication average (%d measured runs, %d request/response exchanges, %d integers each)\n",
           MEASURED_RUNS, ITERATIONS, ARRAY_SIZE);
    for (int run = 1; run <= RUNS; run++) {
        double shared_ms = measure_shared(input);
        double message_ms = measure_message(input);
        if (run > 1) {
            shared_total += shared_ms;
            message_total += message_ms;
        }
    }
    printf("Shared memory: %.6f ms\n", shared_total / MEASURED_RUNS);
    printf("Message passing: %.6f ms\n", message_total / MEASURED_RUNS);
    return 0;
}
