
---

# philosophers – Dining Philosophers Problem

## Description

**philosophers** is a multithreading project that simulates the classic Dining Philosophers Problem using POSIX threads (pthreads).  
The goal is to manage concurrent access to shared resources (forks) while avoiding deadlocks and ensuring data consistency.  
The bonus part includes the implementation of a solution using processes and semaphores.

## Features

- Multithreaded solution using mutexes (mandatory)
- Process-based solution with semaphores (bonus)
- Prevention of deadlocks and starvation
- Precise time management for philosopher actions (eating, sleeping, thinking)
- Clean termination and resource deallocation

## Skills & Concepts Practiced

✔️ Multithreading with `pthread` library  
✔️ Process-based synchronization with semaphores (bonus)  
✔️ Deadlock prevention strategies  
✔️ Race condition and data consistency handling  
✔️ Time management with `usleep`, `gettimeofday`  
✔️ Resource cleanup and graceful exit

## Why this project matters

This project improved my understanding of concurrent programming, synchronization techniques, and inter-process communication — crucial skills for systems development, kernel programming, and real-time applications.

## Project Status

✅ Completed with 125% score (including bonus)

## Usage Example

```bash
./philo 5 800 200 200
# 5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep
