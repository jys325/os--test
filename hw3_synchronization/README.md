# HW3: Synchronization — Race Condition and Mutex

## Overview

In this homework, you will observe a **race condition** that occurs when multiple threads access and modify shared data concurrently.

You will first run a multithreaded program without synchronization and observe its behavior. Then, you will identify the critical section and use a **mutex** to synchronize access to the shared variable.

The goal of this homework is to understand:

- How multiple threads access shared data
- What a race condition is
- What a critical section is
- Why synchronization is necessary
- How a mutex provides mutual exclusion


---

## Environment

This homework should be completed in the provided Docker environment.

Place your homework files in:

```text
/workspace/<your_student_id>/hw3/
```

For example:

```text
/workspace/2026123456/hw3/
```

The starter files provided for this homework are:

```text
race_condition.c
Makefile
```

Compile the program using:

```bash
make
```

Run the program using:

```bash
./race_condition
```


---

# HW3-1: Observe a Race Condition

The provided `race_condition.c` creates two threads that share a global variable named `counter`.

Each thread increments `counter` 1,000,000 times.

Therefore, if every increment is performed correctly, the expected final value is:

```text
2,000,000
```

### Tasks

1. Compile the provided program.

2. Run the program at least **10 times**.

You may use the following command:

```bash
for i in {1..10}; do ./race_condition; done
```

3. Compare the actual final value of `counter` with the expected value.

4. Observe whether the final value changes between executions.

5. Include a screenshot showing the results of multiple executions.

### Questions

Answer the following questions in your report:

1. Did every execution produce the expected value of 2,000,000?
2. Did the final value change between executions?


---

# HW3-2: Analyze the Race Condition

In the provided program, both threads execute:

```c
counter++;
```

The variable `counter` is shared by both threads.

Although `counter++` appears to be a single statement in C, it is not necessarily performed as one indivisible operation. Conceptually, it involves:

1. Reading the current value of `counter`
2. Incrementing the value
3. Writing the new value back to `counter`

When multiple threads perform these operations concurrently, their operations may interfere with each other.

### Questions

Answer the following questions:

1. Why can the final value of `counter` be smaller than 2,000,000?

2. What is the **shared variable** in this program?

3. What part of the program is the **critical section**?

4. Explain what a **race condition** means in the context of this program.


---

# HW3-3: Synchronize Using a Mutex

Modify `race_condition.c` so that the race condition is prevented using a **POSIX mutex**.

Your program should ensure that only one thread can modify `counter` at a time.

You may refer to the following POSIX thread features:

```c
pthread_mutex_t
pthread_mutex_lock()
pthread_mutex_unlock()
```

After modifying the program, compile it again:

```bash
make clean
make
```

Then run the program at least **10 times**:

```bash
for i in {1..10}; do ./race_condition; done
```

### Tasks

1. Declare and initialize a mutex.

2. Use the mutex to protect the critical section.

3. Run the modified program at least 10 times.

4. Include a screenshot showing the results after applying the mutex.


---

# HW3-4: Compare the Results

Compare the behavior of the program **before and after synchronization**.

### Questions

Answer the following questions:

1. What happened to the final value of `counter` before using the mutex?

2. What happened after using the mutex?

3. Why does the mutex prevent the race condition?

4. What happens when one thread attempts to lock the mutex while another thread already holds the lock?

Briefly explain how mutual exclusion changes the behavior of the program.


---

# Screenshot Requirements

Your report must contain the following screenshots.

### Screenshot 1: Before Using the Mutex

Show multiple executions of the original program.

The screenshot should demonstrate the behavior of the program without synchronization.

### Screenshot 2: After Using the Mutex

Show multiple executions after modifying the program to use a mutex.

The screenshot should demonstrate the behavior of the synchronized program.

### Important

Your screenshots must show a directory path containing your **student ID**.

For example:

```text
/workspace/2026123456/hw3/
```

Make sure that the required execution results and your student ID are clearly visible in the screenshots.


---

# Submission

Submit the following two files:

```text
<your_student_id>_HW3.c
<your_student_id>_HW3.pdf
```

For example:

```text
2026123456_HW3.c
2026123456_HW3.pdf
```

## C Source File

`<your_student_id>_HW3.c`

Your C source file should contain your **final implementation using a mutex**.

The program must compile and run in the provided Docker environment.


## PDF Report

`<your_student_id>_HW3.pdf`

Your report should contain:

- Answers to the questions in HW3-1
- Answers to the questions in HW3-2
- Results of your mutex implementation in HW3-3
- Answers to the questions in HW3-4
- Screenshot before using the mutex
- Screenshot after using the mutex


---

# Notes

- Use the provided Docker environment.
- Do not change `NUM_THREADS` or `ITERATIONS`.
- Your program must use POSIX threads (`pthread`).
- Your final program must use a mutex to protect the shared counter.
- Make sure your program compiles successfully using the provided `Makefile`.