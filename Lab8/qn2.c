#include <stdio.h>

long long countCombinations(int C[], int n, int V) {
    long long dp[V + 1];
    
    for (int i = 0; i <= V; i++) {
        dp[i] = 0;
    }
    
    dp[0] = 1; // Base case
    
    for (int i = 0; i < n; i++) {
        for (int j = C[i]; j <= V; j++) {
            dp[j] += dp[j - C[i]];
        }
    }
    
    return dp[V];
}

int main() {
    int C[] = {1, 2, 5};
    int n = sizeof(C) / sizeof(C[0]);
    int V = 5;
    
    printf("Total distinct combinations: %lld\n", countCombinations(C, n, V));
    return 0;
}
