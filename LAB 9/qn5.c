#include <stdio.h>

int candy(int ratings[], int n) {
    int candies[100];
    for (int i = 0; i < n; i++) candies[i] = 1;
    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[i - 1]) candies[i] = candies[i - 1] + 1;
    }
    int totalCandies = candies[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1] && candies[i] <= candies[i + 1]) {
            candies[i] = candies[i + 1] + 1;
        }
        totalCandies += candies[i];
    }
    return totalCandies;
}

int main() {
    int ratings[] = {1, 0, 2};
    printf("Min candies: %d\n", candy(ratings, 3));
    return 0;
}
