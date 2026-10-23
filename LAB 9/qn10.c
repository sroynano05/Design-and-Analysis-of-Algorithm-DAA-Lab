#include <stdio.h>
#include <string.h>

int computeOverlap(char* s1, char* s2) {
    int len1 = strlen(s1), len2 = strlen(s2);
    int maxOverlap = 0;
    int minLen = len1 < len2 ? len1 : len2;
    for (int i = 1; i <= minLen; i++) {
        if (strncmp(s1 + len1 - i, s2, i) == 0) maxOverlap = i;
    }
    return maxOverlap;
}

void greedySuperstring(char* strings[], int n) {
    char arr[20][100];
    int active[20];
    for (int i = 0; i < n; i++) { strcpy(arr[i], strings[i]); active[i] = 1; }
    for (int count = 0; count < n - 1; count++) {
        int maxOver = -1, lIdx = -1, rIdx = -1;
        for (int i = 0; i < n; i++) {
            if (!active[i]) continue;
            for (int j = 0; j < n; j++) {
                if (i == j || !active[j]) continue;
                int over = computeOverlap(arr[i], arr[j]);
                if (over > maxOver) { maxOver = over; lIdx = i; rIdx = j; }
            }
        }
        char temp[200];
        strcpy(temp, arr[lIdx]);
        strcat(temp, arr[rIdx] + maxOver);
        strcpy(arr[lIdx], temp);
        active[rIdx] = 0;
    }
    for (int i = 0; i < n; i++) {
        if (active[i]) printf("Greedy Superstring Result: %s (Length: %lu)\n", arr[i], strlen(arr[i]));
    }
}

int main() {
    char* S[] = {"CATGC", "CTAAGT", "GCTA", "TTCA"};
    greedySuperstring(S, 4);
    return 0;
}
