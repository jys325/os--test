# HW2: Interprocess Communication — shared memory, message passing [Total TBD points]

### Goal
This assignment aims to help students understand interprocess communication (IPC) through hands-on practice with shared memory and message passing, and explain their performance differences based on the lecture materials.

Use C in the same Linux Docker environment as HW1. The `fork()` and `waitpid()` structure is provided; review HW1 if needed.

---

## HW2-1: Shared Memory [TBD points]

Complete the two marked sections in `shared_memory_example.c` so that the parent and child exchange data using **shared memory (`mmap`)**.

- In the **parent process**, write 100 integers (1 through 100). 
- In the **child process**, read the array, calculate its sum, and write the result to shared memory.
- In the **parent process**, wait for the child to terminate, then read the result and verify that it matches the expected sum.
- Unmap shared memory after use. This example uses an anonymous shared mapping, so no named object needs to be removed.

Complete only the two marked sections in `shared_memory_example.c`: copy the parent's input array into shared memory, and calculate and store the sum in the child. Shared memory setup, synchronization, output, result verification, and cleanup code are provided.

### Hints
#### SharedData structure
```
typedef struct {
    int values[ARRAY_SIZE];
    int sum;
} SharedData;
```
- values[ARRAY_SIZE]: Stores an array of integers.
- sum: Stores the sum of the array elements.
- Use a loop to copy the input into `shared->values[i]`.
- Calculate the sum from `shared->values` and store it in `shared->sum`; do not hard-code the answer.

The evidence must show the child's calculated sum and the parent's verification of the returned result.

> Include a terminal screenshot as evidence in your report.
**

---

## HW2-2: Message Passing [TBD points]

Complete the two marked sections in `message_passing_example.c` so that the parent and child perform the same task as HW2-1 using **POSIX message queues**.

- Use separate POSIX message queues for requests and responses.
- In the **parent process**, send the integer array as a request message.
- In the **child process**, receive the array, calculate its sum, and send the result as a response message.
- In the **parent process**, receive the response and verify that it matches the expected sum.
- Close and unlink both message queues after communication.

Use the same input data and computation as HW2-1. Complete only two sections in `message_passing_example.c`: send the parent's array and send the child's result using `mq_send()`. Queue setup, receiving, calculation, and cleanup are provided.

### Hints

- Use `mq_send()` to send a message.
- The request message contains 100 integers and the response message contains one sum.

- `mq_send(queue, message, message_size, priority)`;
The evidence must show the child's calculated sum and the parent's verification of the returned result.

`queue`: Message queue descriptor. In this assignment, you can use request and response queue. ex mq_send(request,...,)

`message`:
Address of the data to send ex)mq_send(...,&a,...)


`message_size`: Size of the data in bytes. you can use sizeof() method. ex) sizeof(a) 

`priority`: Message priority; 0 is sufficient for this assignment

> Include a terminal screenshot as evidence in your report.


---

## HW2-3: Performance Comparison and Analysis [TBD points]

Run the provided `ipc_benchmark.c`, which contains separate shared-memory and POSIX message-passing implementations for comparison. 

Compare the execution times of shared memory and message passing, and explain why there is a difference based on the concepts covered in the operating systems course.
- Both programs use **100 integers**, repeating 1 through 100, with an expected sum of **5,050**.
- Process creation and IPC setup occur before timing.
- The timed interval contains **1,000 request/response exchanges**: sending the 100-integer array, calculating its sum, and receiving the result repeatedly. Output and cleanup are excluded.
- The program prints one total time for shared memory and one for the message queue. Repeating the exchange makes the comparison less sensitive to one short scheduling delay.

### Build & Run

Complete the two sections in each example, then run from the directory containing the source files in the course Linux Docker environment:

```bash
gcc -O2 shared_memory_example.c -o shared_memory_example
gcc -O2 message_passing_example.c -o message_passing_example -lrt
gcc -O2 ipc_benchmark.c -o ipc_benchmark -pthread -lrt
./ipc_benchmark
```

### Analysis Questions

1. Record the two measured times in a table. Which method was faster in this run?
2. Based on lecture slide **140**, explain why shared memory is generally expected to have lower communication overhead than message passing in terms of **system calls and kernel intervention**.
3. Based on lecture slide **141**, explain why shared-memory access needs ordering. How do writing before `fork()` and reading after `waitpid()` ensure the order in HW2-1?
4. Explain how the measured interval isolates IPC communication and which costs are excluded.

Use `2026-OS-L3B-Processes_Part2.pdf`. Slide numbers refer to the numbers printed on the slides, not the PDF viewer's page numbers.

> Include a terminal screenshot of the timing results and a measurement table in your report.

> **[Screenshot placeholder: execution times of HW2-1 and HW2-2]**

---

## Useful Commands (Optional)

```bash
ps -ef
cat /proc/<PID>/status
cat /proc/<PID>/maps
ls -l /proc/<PID>/fd
```

**Tip:** These inspection commands are optional. The examples finish quickly, so their `/proc/<PID>` entries may disappear before inspection. Do not add delays to the programs used for timing. To open a second terminal:

```bash
docker exec -it os-lab bash
```

---

## Report Requirements (HW2-1 to HW2-3)

1. Explain the code you wrote in each of the two marked sections of both example files, and describe how each IPC method transfers data.
2. Describe which **commands** you used to verify the behavior.
3. Include **terminal screenshots** demonstrating successful communication and correct results.
4. Include the HW2-3 measurement table and answers to the analysis questions.
5. **Identity proof:** Your working directory must contain your student ID, e.g.:

   ```text
   /workspace/2026123456/hw2/
   ```

   All screenshots must clearly show this path to prove ownership.

   Screen capture example including your student ID:

> **[Screenshot placeholder: terminal showing the working directory with student ID]**

## Submission

You must submit the following. The required file names are **TBD**.

1. **Completed source files for shared memory and message passing**. The provided benchmark does not need to be submitted.
2. **Report for HW2-1 to HW2-3** in PDF format.

## Important!

1. Total points, per-task points, and deductions are **TBD**.
2. All implementations must compile and run in the course Linux Docker environment.
3. Please strictly follow the Report Requirements and Submission guidelines.
4. Please carefully follow the requirements for each task, including IPC resource cleanup.
5. Performance analysis is evaluated based on consistent measurement conditions and valid explanations. Shared memory is not required to be faster in every measurement.
6. The late submission penalty is **TBD**.
7. This is a draft. Example starter files and the completed benchmark are provided.
