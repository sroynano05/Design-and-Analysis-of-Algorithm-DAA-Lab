# 1D Array Operations & Complexity Analysis

This repository contains a comprehensive C program that implements and benchmarks 9 fundamental 1D array operations on unsorted integer datasets. It includes complete performance mapping for both **Worst-Case** and **Average-Case** computational complexities.

---

## 📊 Complexity Reference Table

| Operation | Worst-Case | Average-Case | Algorithmic Mechanism |
| :--- | :---: | :---: | :--- |
| **(i) Finding the maximum element** | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | Single-pass linear scan tracking the max variable. |
| **(ii) Finding first and second largest** | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | Single-pass linear scan tracking two high bounds. |
| **(iii) Finding the mean** | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | Summation of n elements followed by a division. |
| **(iv) Finding the median** | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n)$ | **Worst:** Merge Sort + index offset. <br>**Average:** Quickselect (Randomised Pivot Selection). |
| **(v) Finding standard deviation** | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | Two-pass calculations (Mean computation → variance). |
| **(vi) Finding the mode** | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n)$ | **Worst:** Comparison Sort + run-length check. <br>**Average:** Hash Map frequency aggregation. |
| **(vii) Removing all duplicates** | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n)$ | **Worst:** Sorting + two-pointer shifting. <br>**Average:** Hash Set filtering. |
| **(viii) Reversing the elements** | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | Two-pointer inward swapping ($\lfloor n/2 \rfloor$ steps). |
| **(ix) Partitioning the array** | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | Lomuto/Hoare dual-pointer filtering relative to a pivot. |