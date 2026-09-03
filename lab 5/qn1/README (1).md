# Complexity Analysis: Median Finding Without Sorting (Buffer-Based Quickselect)

This document provides a comprehensive complexity analysis for the recursive buffer-based median-finding algorithm implemented in C. The algorithm locates the median of a list of $N$ elements without applying a complete sorting pass.

---

## 1. Time Complexity Analysis

The algorithm mirrors the structure of **Quickselect** (Hoare's Selection Algorithm). Instead of dividing and conquering both sides like Quicksort, it drops one partition at each stage.

### Average Case: $\mathcal{O}(N)$
- In each recursive step, a pivot is selected. On average, the pivot splits the array into two sub-arrays of roughly equal size.
- The algorithm recurses into only one sub-array containing the target middle index.
- Total operations follow a geometric series:
  $$N + \frac{N}{2} + \frac{N}{4} + \frac{N}{8} + \dots \approx 2N$$
- Asymptotically, this yields an average time complexity of **$\mathcal{O}(N)$**.

### Best Case: $\mathcal{O}(N)$
- The best-case scenario occurs when the chosen pivot happens to be the exact median element on the first try.
- The loop iterates through the $N$ elements exactly once to partition them, recognizes that the target index falls within the pivot range (`target_idx < j + eq_count`), and immediately returns the pivot.
- Asymptotically, this requires exactly $N$ operations: **$\mathcal{O}(N)$**.

### Worst Case: $\mathcal{O}(N^2)$
- The worst case occurs when the selected pivot consistently lands on the extreme minimum or maximum element of the active range (e.g., when the input list is already sorted or reverse-sorted and the first element is chosen as the pivot).
- Instead of dropping half the elements, only $1$ element (the pivot) is removed at each step.
- The recurrence relation matches:
  $$T(N) = T(N-1) + \mathcal{O}(N)$$
- Total operations follow the arithmetic sum:
  $$N + (N-1) + (N-2) + \dots + 1 = \frac{N(N+1)}{2}$$
- Asymptotically, this yields a worst-case time complexity of **$\mathcal{O}(N^2)$**.

---

## 2. Space Complexity Analysis

Unlike the standard in-place Quickselect, this specific implementation uses a **Buffer-Based Strategy** to maintain structural clarity and handle duplicates reliably.

### Auxiliary Space: $\mathcal{O}(N)$
- In each recursive call frame, two temporary arrays (`lbuffer` and `rbuffer`) are declared dynamically on the stack with a combined size equal to the current sub-problem size (`size`).
- At the top call frame, the buffer allocations require $2 \times N \times \text{sizeof(int)}$ bytes.
- Because these buffers are allocated locally within each recursive step, the peak auxiliary memory usage is bound directly by the largest frame: **$\mathcal{O}(N)$**.

### Call Stack Depth Space
- **Average Case:** $\mathcal{O}(\log N)$ call frames are pushed to the stack as the array is split down evenly.
- **Worst Case:** $\mathcal{O}(N)$ call frames are pushed to the stack during highly skewed partitioning (extreme pivots).

---

## Summary Comparison Table

| Scenario | Time Complexity | Space Complexity (Buffers + Stack) | Reason / Condition |
| :--- | :--- | :--- | :--- |
| **Best Case** | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | Pivot is the median on the first pass. |
| **Average Case** | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | Pivots divide subsets reasonably well. |
| **Worst Case** | $\mathcal{O}(N^2)$ | $\mathcal{O}(N)$ (Stack: $\mathcal{O}(N)$) | Array is sorted / pivots are consistently extreme. |
