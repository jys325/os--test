/**
 * HW2-2: Message Passing
 *
 * Complete the two marked sections:
 * 1. Parent: send input to the child through the request queue.
 * 2. Child: send the calculated sum through the response queue.
 *
 * POSIX message-queue setup, receiving, calculation, and cleanup are provided.
 * Input: 100 integers, repeating 1 through 100 
 *
 * Build (Linux):
 *   gcc message_passing_example.c -o message_passing_example -lrt
 */

#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define ARRAY_SIZE 100

static void parent_send(mqd_t request) {
    int input[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) input[i] = i % 100 + 1;

    // TODO 1: Send input to the child with mq_send().

}

int main(void) {
    char request_name[64], response_name[64];
    snprintf(request_name, sizeof(request_name), "/hw2_req_%ld", (long)getpid());
    snprintf(response_name, sizeof(response_name), "/hw2_res_%ld", (long)getpid());

    struct mq_attr attr = {0};
    attr.mq_maxmsg = 2;
    attr.mq_msgsize = sizeof(int) * ARRAY_SIZE;
    mqd_t request = mq_open(request_name, O_CREAT | O_RDWR, 0600, &attr);
    struct mq_attr response_attr = attr;
    response_attr.mq_msgsize = sizeof(int);
    mqd_t response = mq_open(response_name, O_CREAT | O_RDWR, 0600, &response_attr);
    if (request == (mqd_t)-1 || response == (mqd_t)-1) {
        perror("mq_open");
        if (request != (mqd_t)-1) mq_close(request);
        if (response != (mqd_t)-1) mq_close(response);
        mq_unlink(request_name);
        mq_unlink(response_name);
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }
    if (pid == 0) {
        int values[ARRAY_SIZE], sum = 0;
        if (mq_receive(request, (char *)values, sizeof(values), NULL) == -1) {
            perror("mq_receive");
            return 1;
        }
        for (int i = 0; i < ARRAY_SIZE; i++) sum += values[i];
        printf("Child sum: %d\n", sum);

        // TODO 2: Send sum to the parent with mq_send(response, ...).

        mq_close(request); mq_close(response);
        return 0;
    }

    parent_send(request);
    int sum = 0, status;
    if (mq_receive(response, (char *)&sum, sizeof(sum), NULL) == -1) {
        perror("mq_receive");
        return 1;
    }
    waitpid(pid, &status, 0);
    printf("Parent received sum: %d\n", sum);
    mq_close(request); mq_close(response);
    mq_unlink(request_name); mq_unlink(response_name);
    return WIFEXITED(status) && WEXITSTATUS(status) == 0 ? 0 : 1;
}
