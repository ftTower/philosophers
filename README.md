# Philosophers Project

## Introduction

The **Philosophers** project is a simulation of the classic "Dining Philosophers" problem, implemented in C using threads and mutexes. This problem is a well-known example in computer science, illustrating issues of synchronization, deadlock prevention, and resource sharing among concurrent processes. In this project, each philosopher is represented as a thread, and the forks they need to eat are protected by mutexes.

## Project Overview

This project involves the following key components:

- **Philosophers**: Represented as threads, each philosopher alternates between eating, thinking, and sleeping. A philosopher can only eat if they successfully pick up both the fork on their left and the fork on their right.
- **Forks**: There are as many forks as philosophers. Each fork is shared between two neighboring philosophers and is protected by a mutex to avoid race conditions.
- **Simulation**: The simulation runs until one of the philosophers dies from starvation or until all philosophers have eaten a specified number of times.

## Program Requirements

### Arguments

The program `philo` should be executed with the following arguments:

1. `number_of_philosophers`: The number of philosophers (and forks) at the table.
2. `time_to_die` (in milliseconds): The maximum time a philosopher can go without eating before they die.
3. `time_to_eat` (in milliseconds): The time it takes for a philosopher to eat.
4. `time_to_sleep` (in milliseconds): The time a philosopher spends sleeping.
5. `number_of_times_each_philosopher_must_eat` (optional): If provided, the simulation stops when each philosopher has eaten this number of times.

### Rules and Constraints

- Each philosopher must take both their left and right forks to eat.
- Philosophers must release both forks after eating and then proceed to sleep.
- The program must ensure that no philosopher dies of starvation if it can be avoided.
- The program must handle synchronization issues properly to prevent data races, deadlocks, and resource contention.
- The output logs must clearly indicate the state of each philosopher at each timestamp (e.g., taking a fork, eating, sleeping, thinking, or dying).

### Output Format

The program should output the state of each philosopher in the following format:

[timestamp_in_ms] X has taken a fork
[timestamp_in_ms] X is eating
[timestamp_in_ms] X is sleeping
[timestamp_in_ms] X is thinking
[timestamp_in_ms] X died

Where `timestamp_in_ms` is the current time in milliseconds and `X` is the philosopher's number.

## Compilation and Execution

### Makefile

The project includes a `Makefile` with the following rules:

- **`$(NAME)`**: Compiles the project.
- **`all`**: Compiles the project.
- **`clean`**: Removes object files.
- **`fclean`**: Removes object files and the executable.
- **`re`**: Recompiles the project after cleaning.
- **`bonus`**: Compiles the bonus part of the project (if applicable).

### Compilation

To compile the project, run the following command:

```bash
make
```

Execution
To run the program, use the following syntax:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Additional Notes
Memory Management: Ensure that all dynamically allocated memory is properly freed to avoid memory leaks.
Error Handling: The program should handle all possible errors gracefully, such as invalid arguments or memory allocation failures.
Synchronization: Proper synchronization is crucial to avoid race conditions and ensure that the simulation runs correctly.

Conclusion
This project serves as an excellent exercise in concurrent programming, synchronization, and resource management. By carefully adhering to the requirements and handling synchronization properly, you can create a robust and functional solution to the Dining Philosophers problem.
make
