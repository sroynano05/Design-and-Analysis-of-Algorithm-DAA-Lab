#include <stdio.h>
#include <limits.h>

void maxHeapify(int heap[], int size, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < size && heap[left] > heap[largest]) largest = left;
    if (right < size && heap[right] > heap[largest]) largest = right;
    if (largest != i) {
        int tmp = heap[i]; heap[i] = heap[largest]; heap[largest] = tmp;
        maxHeapify(heap, size, largest);
    }
}

int minimumDeviation(int nums[], int n) {
    int heap[100], minVal = INT_MAX;
    for (int i = 0; i < n; i++) {
        int val = (nums[i] % 2 != 0) ? nums[i] * 2 : nums[i];
        heap[i] = val;
        if (val < minVal) minVal = val;
    }
    for (int i = n / 2 - 1; i >= 0; i--) maxHeapify(heap, n, i);
    int minDev = INT_MAX;
    while (1) {
        int maxVal = heap[0];
        int dev = maxVal - minVal;
        if (dev < minDev) minDev = dev;
        if (maxVal % 2 != 0) break;
        heap[0] = maxVal / 2;
        if (heap[0] < minVal) minVal = heap[0];
        maxHeapify(heap, n, 0);
    }
    return minDev;
}

int main() {
    int nums[] = {4, 1, 5, 20};
    printf("Min deviation: %d\n", minimumDeviation(nums, 4));
    return 0;
}
