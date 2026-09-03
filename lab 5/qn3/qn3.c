#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
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

    quick_sort(arr, 0, n - 1);

    FILE *fout = fopen("sorted_quick.txt", "w");
    if (!fout) { free(arr); return 1; }
    for (int i = 0; i < n; i++) {
        fprintf(fout, "%d\n", arr[i]);
    }
    fclose(fout);

    free(arr);
    return 0;
}
