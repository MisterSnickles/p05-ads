# Quicksort Pivot Strategies vs. Mergesort Performance Analysis

**Course:** CMSC 3613  
**Assignment:** Programming Assignment 05  
**Language:** C++  

## Project Overview
This project evaluates the performance of the Quicksort algorithm using various pivot selection strategies and compares them against Mergesort. The goal is to analyze how different pivot choices affect sorting time and to visualize the growth trend ($O(N \log N)$ vs $O(N^2)$) as the input array size increases.

The program generates random integer arrays, sorts them using 5 different Quicksort variations and Mergesort, records the execution time, and averages the results over multiple trials to ensure a fair comparison. We used Excel to graph these statistics.

## Implemented Algorithms

### Quicksort Strategies
The `Sortable` class implements Quicksort with the following pivot selection strategies:
1.  **Pivot Option 1:** First element as pivot.
2.  **Pivot Option 2:** Randomly chosen pivot.
3.  **Pivot Option 3:** Median of 3 randomly selected elements.
4.  **Pivot Option 4:** Median of the first, center, and last elements.
5.  **Default:** Last element (Baseline implementation).

### Mergesort
* Standard recursive implementation (Divide and Conquer).

## File Structure

* `main.cpp`: Driver program. Handles data generation, runs the sorting tests loops, and writes raw data to the `output/` directory.
* `Sortable.h`: Template class containing the sorting logic (`quick_sort`, `merge_sort`) and helper functions (`partition`, `swap`).
* `utility.h`: Helper enumerations for error handling (referenced in Sortable).
* `output/`: Directory created automatically to store `.dat` result files.

## Compilation and Execution

### 1. Compile the C++ Program
Use `g++` to compile the source code. The assignment requires the executable to be named `p05`.

```bash
g++ -o p05 main.cpp
