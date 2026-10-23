#include <stdio.h>
#include <stdlib.h>

struct Station {
    int dist, fuel;
};

int compareStations(const void* a, const void* b) {
    return ((struct Station*)a)->dist - ((struct Station*)b)->dist;
}

int minRefuelStops(int target, int startFuel, struct Station stations[], int n) {
    qsort(stations, n, sizeof(struct Station), compareStations);
    int heap[100], heapSize = 0, stops = 0, maxReach = startFuel, i = 0;
    while (maxReach < target) {
        while (i < n && stations[i].dist <= maxReach) {
            heap[heapSize++] = stations[i].fuel;
            int c = heapSize - 1;
            while (c > 0 && heap[c] > heap[(c - 1) / 2]) {
                int tmp = heap[c]; heap[c] = heap[(c - 1) / 2]; heap[(c - 1) / 2] = tmp;
                c = (c - 1) / 2;
            }
            i++;
        }
        if (heapSize == 0) return -1;
        int maxFuel = heap[0];
        heap[0] = heap[--heapSize];
        int p = 0;
        while (2 * p + 1 < heapSize) {
            int left = 2 * p + 1, right = 2 * p + 2, largest = left;
            if (right < heapSize && heap[right] > heap[left]) largest = right;
            if (heap[p] >= heap[largest]) break;
            int tmp = heap[p]; heap[p] = heap[largest]; heap[largest] = tmp;
            p = largest;
        }
        maxReach += maxFuel;
        stops++;
    }
    return stops;
}

int main() {
    struct Station s[] = {{10, 60}, {20, 30}, {30, 30}, {60, 40}};
    printf("Min stops: %d\n", minRefuelStops(100, 10, s, 4));
    return 0;
}
