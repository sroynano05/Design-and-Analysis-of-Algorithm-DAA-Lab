#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L); free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int findMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];
    return max;
}

void findFirstAndSecondLargest(int arr[], int n, int *first, int *second) {
    *first = arr[0]; *second = -1;
    for (int i = 1; i < n; i++) {
        if (arr[i] > *first) { *second = *first; *first = arr[i]; }
        else if (arr[i] > *second && arr[i] != *first) *second = arr[i];
    }
}

double findMean(int arr[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return sum / n;
}

double findMedian(int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) temp[i] = arr[i];
    mergeSort(temp, 0, n - 1);
    double med = (n % 2 != 0) ? temp[n / 2] : (temp[(n - 1) / 2] + temp[n / 2]) / 2.0;
    free(temp);
    return med;
}

double findStandardDeviation(int arr[], int n) {
    double mean = findMean(arr, n), sumSqDiff = 0;
    for (int i = 0; i < n; i++) sumSqDiff += (arr[i] - mean) * (arr[i] - mean);
    return sqrt(sumSqDiff / n);
}

int findMode(int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) temp[i] = arr[i];
    mergeSort(temp, 0, n - 1);
    int mode = temp[0], maxCount = 1, currentCount = 1;
    for (int i = 1; i < n; i++) {
        if (temp[i] == temp[i - 1]) currentCount++;
        else {
            if (currentCount > maxCount) { maxCount = currentCount; mode = temp[i - 1]; }
            currentCount = 1;
        }
    }
    if (currentCount > maxCount) mode = temp[n - 1];
    free(temp);
    return mode;
}

int removeDuplicates(int arr[], int n) {
    if (n <= 1) return n;
    mergeSort(arr, 0, n - 1);
    int j = 0;
    for (int i = 0; i < n - 1; i++) if (arr[i] != arr[i + 1]) arr[j++] = arr[i];
    arr[j++] = arr[n - 1];
    return j;
}

void reverseArray(int arr[], int n) {
    int start = 0, end = n - 1;
    while (start < end) swap(&arr[start++], &arr[end--]);
}

int partitionArray(int arr[], int n, int pivotValue) {
    int i = 0;
    for (int j = 0; j < n; j++) if (arr[j] >= pivotValue) swap(&arr[i++], &arr[j]);
    return i;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3}, n = sizeof(arr) / sizeof(arr[0]);
    int t1[10], t2[10], t3[10], first, second;
    
    printf("Original: "); printArray(arr, n);
    printf("(i) Max: %d\n", findMax(arr, n));
    findFirstAndSecondLargest(arr, n, &first, &second);
    printf("(ii) 1st: %d, 2nd: %d\n", first, second);
    printf("(iii) Mean: %.2f\n", findMean(arr, n));
    printf("(iv) Median: %.2f\n", findMedian(arr, n));
    printf("(v) StdDev: %.2f\n", findStandardDeviation(arr, n));
    printf("(vi) Mode: %d\n", findMode(arr, n));
    
    for(int i=0; i<n; i++) { t1[i]=arr[i]; t2[i]=arr[i]; t3[i]=arr[i]; }
    reverseArray(t1, n); printf("(viii) Reversed: "); printArray(t1, n);
    partitionArray(t2, n, 4); printf("(ix) Partitioned (Pivot 4): "); printArray(t2, n);
    int sz = removeDuplicates(t3, n); printf("(vii) Unique: "); printArray(t3, sz);
    return 0;
}
