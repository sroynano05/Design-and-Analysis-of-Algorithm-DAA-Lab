# Sorting via Reversal Analysis & Implementation

## 1. Mathematical Proof for O(n) Reversals
Using a selection-based approach, we can place one element in its correct position per step:
1. **Step 1:** Locate element `1` at index $k$. If $k \neq 1$, invoke `reverse(p, 1, k)`. Element `1` is now at index 1.
2. **Step i:** Assume the prefix `[1...i-1]` is sorted. Find element `i` at index $k \ge i$. If $k \neq i$, invoke `reverse(p, i, k)`. The prefix remains unaffected.
3. **Termination:** Repeat up to $i = n-1$. The last element $n$ falls into place automatically.

**Complexity:** Each step uses at most $1$ reversal. For $n-1$ steps, the maximum number of reversals is $n-1 = O(n)$.

---

## 2. O(n log² n) Cost Algorithm Design
When the cost of `reverse(p, i, j)` is its length ($|j - i| + 1$), we apply a stable divide-and-conquer strategy:

```
Algorithm: reversal_sort(p, low, high)
1. If low >= high, return.
2. mid_val = low + 1 + (high - low) / 2
3. partition_by_value(p, low, high, mid_val)
4. mid_idx = low + (high - low) / 2
5. reversal_sort(p, low, mid_idx)
6. reversal_sort(p, mid_idx + 1, high)

Algorithm: partition_by_value(p, low, high, mid_val)
1. If low >= high, return.
2. m = low + (high - low) / 2
3. partition_by_value(p, low, m, mid_val)
4. partition_by_value(p, m + 1, high, mid_val)
5. Find first i_start in [low...m] where p[i] > mid_val.
6. Find last j_end in [m+1...high] where p[j] <= mid_val.
7. If both exist, invoke reverse(p, i_start, j_end).
```

---

## 3. Complexity & Correctness Proof

### Correctness
* **Partitioning:** Subarrays are divided down to base cases of size 1. The combine step performs a single reversal over `[i_start...j_end]`, taking blocks structured as `[(> mid_val) | (<= mid_val)]` and transforming them into `[(<= mid_val)^R | (> mid_val)^R]`. This stably groups elements relative to `mid_val`.
* **Sorting:** Global values are split recursively down to base singletons, ensuring full sorted order.

### Reversal Cost & Runtime Analysis
Let $C_P(n)$ be the partition cost for size $n$:
$$C_P(n) = 2 C_P(n/2) + \text{cost}(\text{middle reversal}) \le 2 C_P(n/2) + n \implies C_P(n) = O(n \log n)$$

Let $C_S(n)$ be the total sort cost for size $n$:
$$C_S(n) = 2 C_S(n/2) + C_P(n) = 2 C_S(n/2) + O(n \log n)$$

Summing across all $\log n$ levels of the recursion tree:
$$\sum_{k=0}^{\log n} 2^k \cdot O\left(\frac{n}{2^k} \log \frac{n}{2^k}\right) = \sum_{k=0}^{\log n} O(n \log n - n k) = O(n \log^2 n)$$
Since tracking pointers and indices takes linear time per step matching the reversal lengths, the overall execution time matches the cost at **$O(n \log^2 n)$**.

---

## 4. C Program Validation

```c
#include <stdio.h>
#include <stdlib.h>

long long total_reversal_cost = 0;
int reversal_count = 0;

void reverse(int *p, int i, int j) {
    if (i >= j) return;
    total_reversal_cost += (j - i + 1);
    reversal_count++;
    while (i < j) {
        int temp = p[i];
        p[i] = p[j];
        p[j] = temp;
        i++; j--;
    }
}

void partition_by_value(int *p, int low, int high, int mid_val) {
    if (low >= high) return;
    int m = low + (high - low) / 2;
    partition_by_value(p, low, m, mid_val);
    partition_by_value(p, m + 1, high, mid_val);
    
    int i_start = -1, j_end = -1;
    for (int i = low; i <= m; i++) {
        if (p[i] > mid_val) { i_start = i; break; }
    }
    for (int j = high; j >= m + 1; j--) {
        if (p[j] <= mid_val) { j_end = j; break; }
    }
    if (i_start != -1 && j_end != -1) {
        reverse(p, i_start, j_end);
    }
}

void reversal_sort(int *p, int low, int high) {
    if (low >= high) return;
    int mid_val = low + 1 + (high - low) / 2;
    partition_by_value(p, low, high, mid_val);
    int mid_idx = low + (high - low) / 2;
    reversal_sort(p, low, mid_idx);
    reversal_sort(p, mid_idx + 1, high);
}

void print_array(int *p, int n) {
    for (int i = 0; i < n; i++) printf("%d ", p[i]);
    printf("\n");
}

int main() {
    int p[] = {5, 1, 4, 2, 8, 6, 3, 7};
    int n = sizeof(p) / sizeof(p[0]);
    
    printf("Original: "); print_array(p, n);
    reversal_sort(p, 0, n - 1);
    printf("Sorted:   "); print_array(p, n);
    printf("\n--- Metrics ---\nReversals: %d\nTotal Cost: %lld\n", reversal_count, total_reversal_cost);
    return 0;
}
```