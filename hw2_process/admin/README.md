# homeworks_admin

## OS 26-1 HW2 Grading Guide

This directory contains grading guidance and reference answers for the OS 26-1 HW2 assignment.

> Administrator use only. Student-facing instructions are in `../README.md`. Scores and deductions remain **TBD**, consistent with the student-facing draft.

---

## HW2 Grading Criteria

### Source Code Grading Criteria (HW2-1 ~ HW2-2)

The source code score is based on a total of **TBD points**.

| Criteria | Deduction |
| --- | ---: |
| Compile error or failure to complete execution | TBD |
| HW2-1: The parent does not copy all 100 input elements into shared memory before `fork()` | TBD |
| HW2-1: The child does not calculate the sum from the shared array and store it in `shared->sum` | TBD |
| HW2-2: The child does not send the sum through the response message queue | TBD |
| HW2-2: The parent does not send the entire input array through the request message queue | TBD |
| The answer is hard-coded instead of calculated or communicated as required | TBD |

> Both programs must calculate and display the sum **5,050**. Inspect the completed sections as well: the printed result alone does not prove a correct implementation. Accept equivalent correct solutions, not only code identical to the reference answers.

> Process creation, waiting, IPC setup, receiving, synchronization, and cleanup are provided in the starter files. The assessed implementation consists of two marked sections per file. Students do not implement HW2-3's measurement code.

---

### Report Grading Criteria (HW2-1 ~ HW2-3)

Each report item's score is **TBD**.

| Criteria | Score |
| --- | ---: |
| HW2-1 and HW2-2: Terminal screenshots and explanations of the completed sections are included | TBD |
| Screenshots show the working directory path containing the student ID | TBD |
| HW2-3: The shared-memory and message-queue communication times are reported | TBD |
| HW2-3: Observed results and their consistency are discussed | TBD |
| HW2-3: System calls and kernel intervention are used to explain the expected IPC overhead difference (slide 140) | TBD |
| HW2-3: Writing before `fork()` and reading after `waitpid()` are explained (slide 141) | TBD |
| HW2-3: Whole-program timing limitations and possible variation are explained | TBD |

> Terminal screenshots should clearly show the working directory path containing the student ID. Missing evidence and partial-credit amounts are TBD.

> Evaluate the measured communication times and reasoning. See `ipc_benchmark_answer.md` for the reference discussion.

---

### Late Submission Policy

| Criteria | Deduction |
| --- | ---: |
| Submitted before the deadline | No deduction |
| Submitted after the deadline | TBD |

---

## How to Run the HW2 Reference Answers

### Basic Usage

Run from `hw2_process/admin` inside the course Linux Docker environment:

```bash
gcc -O2 -Wall -Wextra shared_memory_example_answer.c -o shared_memory_example
gcc -O2 -Wall -Wextra message_passing_example_answer.c -o message_passing_example -lrt
gcc -O2 -Wall -Wextra ../ipc_benchmark.c -o ipc_benchmark -pthread -lrt
./shared_memory_example
./message_passing_example
./ipc_benchmark
```

The executables are built in `admin`, leaving student starter files and their executables untouched. Keep the executable names shown above: the benchmark launches those names from its current working directory. The existing `../ipc_benchmark.c` is already complete and needs no separate answer copy.

### Example

Each reference implementation should print:

```text
Child sum: 5050
Parent received sum: 5050
```

The benchmark reports the total time for 1,000 repeated communication exchanges for shared memory and for the message queue. Numerical timings vary by environment and are not fixed answer values.

### Arguments

These programs take no command-line arguments. No autograder is included.

---

## Reference Answer Files

| Task | File |
| --- | --- |
| HW2-1: Shared Memory | `shared_memory_example_answer.c` |
| HW2-2: Message Passing | `message_passing_example_answer.c` |
| HW2-3: Performance Comparison and Analysis | `ipc_benchmark_answer.md` |
