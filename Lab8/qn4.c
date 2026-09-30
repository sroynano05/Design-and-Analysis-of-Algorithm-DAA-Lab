#include <stdio.h>
int lengthOfLIS(int* A, int n) {
    if (n == 0) return 0;
    int tails[n];
    int len = 0;
    for (int i = 0; i < n; i++) {
        int low = 0, high = len;
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (tails[mid] < A[i]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }

        // Update or extend the active tail sequence
        tails[low] = A[i];
        if (low == len) {
            len++;
        }
    }

    return len;
}

int main() {
    int A[] = {10, 9, 2, 5, 3, 7, 101, 18};
    int n = sizeof(A) / sizeof(A[0]);

    printf("Input Array: ");
    for (int i = 0; i < n; i++) printf("%d ", A[i]);
    printf("\n");

    printf("Length of Longest Increasing Subsequence: %d\n", lengthOfLIS(A, n));

    return 0;
}
