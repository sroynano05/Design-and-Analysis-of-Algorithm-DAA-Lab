#include <stdio.h>
int find_median(int arr[], int size, int target_idx) {
    int pivot = arr[0];
    int lbuffer[size];
    int rbuffer[size];
    int j = 0; 
    int k = 0;
    int eq_count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] < pivot) {
            lbuffer[j] = arr[i];
            j++;
        } else if (arr[i] > pivot) {
            rbuffer[k] = arr[i];
            k++;
        } else {
            eq_count++;
        }
    }
    if (target_idx < j) {
        return find_median(lbuffer, j, target_idx);
    } else if (target_idx < j + eq_count) {
        return pivot;
    } else {
        return find_median(rbuffer, k, target_idx - j - eq_count);
    }
}

int main() {
    int x;
    printf("Enter elements :\n");
    if (scanf("%d", &x) != 1 || x <= 0) {
        return 1;
    }

    int arr[x];
    for (int i = 0; i < x; i++) {
        printf("Enter the %dth element :", i);
        scanf("%d", &arr[i]);
    }
    int target_idx = x / 2;
    int median = find_median(arr, x, target_idx);
    printf("The pivot Element is : %d\n", median);
    return 0;
}
