#include <stdio.h>
int minCoins(int C[], int n, int V) {
    int dp[V + 1];
    dp[0] = 0;
    for (int i = 1; i <= V; i++) {
        dp[i] = V + 1;
    }
    for (int i = 1; i <= V; i++) {
        for (int j = 0; j < n; j++) {
            if (C[j] <= i) {
                int sub_res = dp[i - C[j]];
                if (sub_res != V + 1 && sub_res + 1 < dp[i]) {
                    dp[i] = sub_res + 1;
                }
            }
        }
    }
    if (dp[V] == V + 1) {
        return -1; 
    }
    return dp[V];
}
int main() {
    int C[] = {1, 2, 5};
    int n = sizeof(C) / sizeof(C[0]);
    int V = 11;
    int result = minCoins(C, n, V);
    printf("Minimum coins required for amount %d: %d\n", V, result);
    return 0;
}
