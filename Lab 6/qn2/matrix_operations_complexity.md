# Matrix Operations and Complexity Analysis

## 1. Complexity Summary Table

| Algorithm | Worst-Case Complexity | Description |
| :--- | :--- | :--- |
| **(i) Matrix Addition** | $O(n^2)$ | Visits all $n^2$ elements exactly once. |
| **(ii) Matrix Multiplication** | $O(n^3)$ | Standard algorithm uses three nested loops ($n \times n \times n$). |
| **(iii) Zero Check** | $O(n^2)$ | Scans up to $n^2$ items before confirming. |
| **(iv) Symmetry Check** | $O(n^2)$ | Compares $\frac{n(n-1)}{2}$ upper and lower triangular pairs. |
| **(v) Determinant** | $O(n^3)$ | Achieved via row reduction (Gaussian elimination). |
| **(vi) Transpose In Situ** | $O(n^2)$ | Swaps $\frac{n(n-1)}{2}$ elements across the main diagonal. |
| **(vii) Eigenpair Discovery** | $O(n^3)$ | Standard iterative solvers (like the QR algorithm) scale cubically. |
