# HW3 Admin Guide

## HW3-1 ~ HW3-4: Race Condition and Mutex

The starter code contains a race condition because two threads modify the shared variable `counter` without synchronization.

The critical section is:

```c
counter++;
```

Students should protect this section using a POSIX mutex.

A correct implementation should use:

```c
pthread_mutex_lock(&mutex);
counter++;
pthread_mutex_unlock(&mutex);
```

After synchronization, repeated executions should consistently produce:

```text
Final counter value: 2000000
Expected counter value: 2000000
```

Reference solution:

```text
race_condition_answer.c
```


---

## HW3-5: Deadlock

The starter `deadlock.c` intentionally creates a deadlock.

Thread 1 acquires the mutexes in the following order:

```text
mutex1 -> mutex2
```

Thread 2 acquires the mutexes in the opposite order:

```text
mutex2 -> mutex1
```

If Thread 1 holds `mutex1` while Thread 2 holds `mutex2`, each thread waits for a mutex held by the other thread.

The resulting situation is:

```text
Thread 1:
holds mutex1
waits for mutex2

Thread 2:
holds mutex2
waits for mutex1
```

Neither thread can continue because each thread is waiting for a resource held by the other thread.

The deadlock can be prevented by enforcing a consistent mutex acquisition order.

For example, both threads can acquire the mutexes in the following order:

```text
mutex1 -> mutex2
```

This prevents the circular wait between the two threads.

Reference solution:

```text
deadlock_answer.c
```


---

## Reference Files

```text
race_condition_answer.c
deadlock_answer.c
```

`race_condition_answer.c` contains the reference solution for the race condition and mutex portion of the homework.

`deadlock_answer.c` contains the reference solution for the deadlock portion of the homework.