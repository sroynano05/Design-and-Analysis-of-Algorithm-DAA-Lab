#include <stdio.h>
long long minMovesToInvert(long long n) {
    if (n <= 0) return 0;
    return (n * (n + 1)) / 6;
}
int main() {
    long long heights[] = {1, 2, 3, 4, 5, 10};
    int numCases = sizeof(heights) / sizeof(heights[0]);

    for (int i = 0; i < numCases; i++) {
        long long h = heights[i];
        printf("Height: %lld, Minimum Moves: %lld\n", h, minMovesToInvert(h));
    }
    return 0;
}
