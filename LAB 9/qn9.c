#include <stdio.h>
#include <limits.h>

void huTuckerSimulation(int w[], int n) {
    int weights[100], active[100], parent[100], leftChild[100], rightChild[100];
    for (int i = 0; i < n; i++) { weights[i] = w[i]; active[i] = 1; parent[i] = -1; }
    int currentNodes = n;
    while (1) {
        int minSum = INT_MAX, targetL = -1, targetR = -1;
        for (int i = 0; i < currentNodes; i++) {
            if (!active[i]) continue;
            int crossSkipped = 0;
            for (int j = i + 1; j < currentNodes; j++) {
                if (!active[j]) continue;
                int sum = weights[i] + weights[j];
                if (sum < minSum) { minSum = sum; targetL = i; targetR = j; }
                break; 
            }
        }
        if (targetL == -1 || targetR == -1) break;
        int newIdx = currentNodes++;
        weights[newIdx] = minSum; active[newIdx] = 1; parent[targetL] = newIdx; parent[targetR] = newIdx;
        leftChild[newIdx] = targetL; rightChild[newIdx] = targetR;
        active[targetL] = 0; active[targetR] = 0;
        active[targetL] = 1; weights[targetL] = minSum; // Left takes over spot for sequence adjacency preservation
    }
    printf("Hu-Tucker Combination simulation root weight: %d\n", weights[currentNodes - 2]);
}

int main() {
    int w[] = {4, 3, 2, 6};
    huTuckerSimulation(w, 4);
    return 0;
}
