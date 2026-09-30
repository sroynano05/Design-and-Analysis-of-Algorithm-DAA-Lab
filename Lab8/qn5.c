#include <stdio.h>
#include <stdlib.h>
int msis(int A[], int n) {
    int *dp = (int *)malloc(n * sizeof(int));
    if (!dp) return -1;
    for (int i = 0; i < n; i++) dp[i] = A[i];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (A[i] > A[j] && dp[i] < dp[j] + A[i]) {
                dp[i] = dp[j] + A[i];
            }
        }
    }
    int max_sum = dp[0];
    for (int i = 1; i < n; i++) {
        if (dp[i] > max_sum) max_sum = dp[i];
    }
    free(dp);
    return max_sum;
}
int main() {
    int A[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(A) / sizeof(A[0]);
    printf("Max Sum: %d\n", msis(A, n)); 
    return 0;
}