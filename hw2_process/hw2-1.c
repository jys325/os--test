/**
 * ============================================================
 * HW2-1: Shared Memory
 * ============================================================
 *
 * Complete the two marked sections:
 * 1. Parent: copy input into shared->values before fork().
 * 2. Child: calculate the array sum and store it in shared->sum.
 *
 * Input: 100 integers, repeating 1 through 100 (sum: 5050).
 * Shared memory setup and cleanup are provided.
 * The parent waits for the child before reading the result.
 * Hint: use a for loop; do not hard-code the answer.
 *
 * Build & Run (Linux):
 *   gcc shared_memory_example.c -o shared_memory_example
 *   ./shared_memory_example
 */

#include <stdio.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define ARRAY_SIZE 100

typedef struct {
    int values[ARRAY_SIZE];
    int sum;
} SharedData;

int main(void) {
    /* This shared mapping is inherited by the child through fork(). */
    SharedData *shared = mmap(NULL, sizeof(SharedData),
        PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    int input[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) input[i] = i % 100 + 1;
    // TODO 1: Copy input[i] into shared->values[i] using a loop.

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        munmap(shared, sizeof(SharedData));
        return 1;
    }

    if (pid == 0) {
        shared->sum = 0;
        // TODO 2: Sum shared->values and store the result in shared->sum.

        printf("Child sum: %d\n", shared->sum);
        munmap(shared, sizeof(SharedData));
        return 0;
    }

    int status;
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        munmap(shared, sizeof(SharedData));
        return 1;
    }
    printf("Parent received sum: %d\n", shared->sum);
    munmap(shared, sizeof(SharedData));
    return WIFEXITED(status) && WEXITSTATUS(status) == 0 ? 0 : 1;
}
