# DAA Lab 02 — Merge Sort vs Modified Merge Sort

## Problem Statement

Consider the following modification to Merge Sort:

- Divide the input array into three parts instead of two.
- Recursively sort each third.
- Combine the results using a three-way merge subroutine.

Determine the worst-case running time of the modified Merge Sort.

A C program is used to validate the result by plotting the order of growth of:

1. Standard Merge Sort
2. Modified Three-Way Merge Sort

The program uses Raylib to display the experimental graph.

## Objective

- Understand the recurrence of standard Merge Sort.
- Derive the recurrence of the modified Merge Sort.
- Apply the Master Theorem.
- Compare the experimental growth of both algorithms.
- Validate the theoretical order of growth using a graph.

## Standard Merge Sort

Standard Merge Sort divides the input into two approximately equal parts.

The recurrence is:

**T(n) = 2T(n/2) + O(n)**

Using the Master Theorem:

- a = 2
- b = 2
- f(n) = O(n)

Therefore:

**T(n) = O(n log n)**

## Modified Three-Way Merge Sort

The modified algorithm divides the input into three approximately equal parts, recursively sorts each part, and combines the three sorted parts using a three-way merge.

The recurrence is:

**T(n) = 3T(n/3) + O(n)**

Using the Master Theorem:

- a = 3
- b = 3
- f(n) = O(n)

Since:

**n^(log_3 3) = n**

the result is:

**T(n) = O(n log n)**

## Complexity Comparison

| Algorithm | Recurrence | Worst-Case Time |
|---|---|---|
| Standard Merge Sort | T(n) = 2T(n/2) + O(n) | O(n log n) |
| Modified Merge Sort | T(n) = 3T(n/3) + O(n) | O(n log n) |

Therefore, both algorithms have the same asymptotic worst-case running time:

**O(n log n)**

The three-way modification changes the constant factors, but not the asymptotic complexity.

## Experimental Validation

The program counts basic operations performed during sorting rather than measuring wall-clock execution time.

Input sizes are generated as:

```text
50, 100, 150, ..., 1500
