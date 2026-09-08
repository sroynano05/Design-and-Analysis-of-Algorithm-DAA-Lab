# Vector Convolution via Divide and Conquer (FFT)

This document contains an $O(n \log n)$ divide-and-conquer implementation for the convolution of two vectors using the Cooley-Tukey Fast Fourier Transform (FFT) algorithm in C.

## Algorithm Description

The convolution of two vectors $A$ (length $m$) and $B$ (length $n$) can be evaluated as polynomial multiplication. By transforming the vectors from the coefficient domain to the point-value domain using the FFT, pointwise multiplying them, and performing the Inverse FFT (IFFT), the operation completes in $O(n \log n)$ time for $n \ge m$.

1. **Zero-Padding**: Pad both vectors to a size $N$ which is the smallest power of 2 such that $N \ge m + n - 1$.
2. **Divide**: Split the polynomial coefficients into even-indexed and odd-indexed terms.
3. **Conquer**: Recursively compute the FFT of both halves.
4. **Combine**: Merge the outputs using the complex roots of unity.

## Complexity Analysis

* **Time Complexity**: $T(N) = 2T(N/2) + O(N) \implies O(N \log N)$. Since $N < 4n$, the overall time complexity is tightly bounded by **$O(n \log n)$** when $n \ge m$.
* **Space Complexity**: **$O(N \log N)$** due to auxiliary array allocations across recursive stack calls.
