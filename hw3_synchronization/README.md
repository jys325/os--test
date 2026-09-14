# HW3: Synchronization — Race Condition, Mutex, and Deadlock

## Overview

In this homework, you will explore synchronization problems that can occur when multiple threads execute concurrently.

You will first observe a **race condition** that occurs when multiple threads access and modify shared data without synchronization.

Then, you will identify the critical section and use a **mutex** to synchronize access to the shared variable.

Finally, you will observe a **deadlock** caused by incorrect mutex usage and modify the program to prevent the deadlock.

The goal of this homework is to understand:

- How multiple threads access shared data
- What a race condition is
- What a critical section is
- Why synchronization is necessary
- How a mutex provides mutual exclusion
- What a deadlock is
- How mutex acquisition order can prevent deadlock


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
deadlock.c
Makefile
```

Compile the programs using:

```bash
make
```

This creates:

```text
race_condition
deadlock
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

Although `counter++` appears to be a single statement in C, it is not necessarily performed as one indivisible operation.

Conceptually, it involves:

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

# HW3-5: Observe and Resolve a Deadlock

The provided `deadlock.c` creates two threads and uses two mutexes.

Each thread acquires the mutexes in a different order.

Run the program:

```bash
./deadlock
```

You may observe output similar to:

```text
Thread 1 acquired mutex1
Thread 2 acquired mutex2
Thread 1 waiting for mutex2
Thread 2 waiting for mutex1
```

The program will then stop making progress.

Use `Ctrl+C` to terminate the program after observing the deadlock.

### Tasks

1. Run the provided `deadlock.c`.

2. Observe where the program stops.

3. Identify which mutex each thread currently holds.

4. Identify which mutex each thread is waiting for.

5. Modify the program so that both threads acquire the mutexes in the same order.

6. Compile the program again:

```bash
make
```

7. Run the modified program and verify that both threads finish successfully.

8. Include screenshots showing the program before and after resolving the deadlock.

### Questions

Answer the following questions:

1. Which mutex is held by Thread 1 when the deadlock occurs?

2. Which mutex is held by Thread 2 when the deadlock occurs?

3. What mutex is Thread 1 waiting for?

4. What mutex is Thread 2 waiting for?

5. Why are the two threads unable to continue?

6. Why does acquiring the mutexes in the same order prevent this deadlock?


---

# Screenshot Requirements

Your report must contain the following screenshots.

### Screenshot 1: Before Using the Mutex

Show multiple executions of `race_condition` before synchronization.

### Screenshot 2: After Using the Mutex

Show multiple executions after modifying `race_condition.c` to use a mutex.

### Screenshot 3: Deadlock

Show the execution of `deadlock` where both threads stop making progress.

### Screenshot 4: After Resolving the Deadlock

Show that both threads successfully finish after modifying the mutex acquisition order.

### Important

Your screenshots must show a directory path containing your **student ID**.

For example:

```text
/workspace/2026123456/hw3/
```

Make sure that the required execution results and your student ID are clearly visible in the screenshots.


---

# Submission

Submit the following three files:

```text
<your_student_id>_HW3_race_condition.c
<your_student_id>_HW3_deadlock.c
<your_student_id>_HW3.pdf
```

For example:

```text
2026123456_HW3_race_condition.c
2026123456_HW3_deadlock.c
2026123456_HW3.pdf
```

## Race Condition Source File

```text
<your_student_id>_HW3_race_condition.c
```

Submit your final `race_condition.c` implementation using a mutex.


## Deadlock Source File

```text
<your_student_id>_HW3_deadlock.c
```

Submit your final `deadlock.c` implementation after preventing the deadlock.


## PDF Report

```text
<your_student_id>_HW3.pdf
```

Your report should contain:

- Answers to the questions in HW3-1
- Answers to the questions in HW3-2
- Results of your mutex implementation in HW3-3
- Answers to the questions in HW3-4
- Answers to the questions in HW3-5
- Screenshot before using the mutex
- Screenshot after using the mutex
- Screenshot showing the deadlock
- Screenshot after resolving the deadlock


---

# Notes

- Use the provided Docker environment.
- Do not change `NUM_THREADS` or `ITERATIONS` in `race_condition.c`.
- Your programs must use POSIX threads (`pthread`).
- Your final `race_condition.c` must use a mutex to protect the shared counter.
- Your final `deadlock.c` must prevent the deadlock by using a consistent mutex acquisition order.
- Make sure both programs compile successfully using the provided `Makefile`.