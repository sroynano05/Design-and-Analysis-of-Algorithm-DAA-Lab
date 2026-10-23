#include <stdio.h>

void minHeapify(int heap[], int size, int i) {
    int smallest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < size && heap[left] < heap[smallest]) smallest = left;
    if (right < size && heap[right] < heap[smallest]) smallest = right;
    if (smallest != i) {
        int tmp = heap[i]; heap[i] = heap[smallest]; heap[smallest] = tmp;
        minHeapify(heap, size, smallest);
    }
}

int connectSticks(int sticks[], int n) {
    int size = n, totalCost = 0;
    for (int i = size / 2 - 1; i >= 0; i--) minHeapify(sticks, size, i);
    while (size > 1) {
        int first = sticks[0];
        sticks[0] = sticks[--size];
        minHeapify(sticks, size, 0);
        int second = sticks[0];
        int cost = first + second;
        totalCost += cost;
        sticks[0] = cost;
        minHeapify(sticks, size, 0);
    }
    return totalCost;
}

int main() {
    int sticks[] = {2, 4, 3};
    printf("Min cost: %d\n", connectSticks(sticks, 3));
    return 0;
}
