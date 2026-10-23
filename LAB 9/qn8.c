#include <stdio.h>
#include <stdlib.h>

int compareInts(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int minMeetingRooms(int starts[], int ends[], int n) {
    qsort(starts, n, sizeof(int), compareInts);
    qsort(ends, n, sizeof(int), compareInts);
    int rooms = 0, j = 0;
    for (int i = 0; i < n; i++) {
        if (starts[i] < ends[j]) rooms++;
        else j++;
    }
    return rooms;
}

int main() {
    int starts[] = {0, 5, 15};
    int ends[] = {30, 10, 20};
    printf("Min rooms: %d\n", minMeetingRooms(starts, ends, 3));
    return 0;
}
