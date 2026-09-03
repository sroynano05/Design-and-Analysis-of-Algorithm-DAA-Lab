#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    srand(time(NULL));
    FILE *fin = fopen("input.txt", "w");
    if (!fin) return 1;
    for (int i = 0; i < n; i++) {
        fprintf(fin, "%d\n", rand() % 10000);
    }
    fclose(fin);

    int *arr = malloc(n * sizeof(int));
    if (!arr) return 1;

    fin = fopen("input.txt", "r");
    if (!fin) { free(arr); return 1; }
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%d", &arr[i]);
    }
    fclose(fin);

    heap_sort(arr, n);

    FILE *fout = fopen("sorted_heap.txt", "w");
    if (!fout) { free(arr); return 1; }
    for (int i = 0; i < n; i++) {
        fprintf(fout, "%d\n", arr[i]);
    }
    fclose(fout);

    free(arr);
    return 0;
}
