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
