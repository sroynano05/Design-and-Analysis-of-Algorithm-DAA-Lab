#include <stdio.h>
#include <stdlib.h>
struct Event {
    int year;
    int type; 
};
int compare(const void* a, const void* b) {
    struct Event* e1 = (struct Event*)a;
    struct Event* e2 = (struct Event*)b;
    if (e1->year != e2->year) return e1->year - e2->year;
    return e1->type - e2->type;
}
int findBestTime(struct Event events[], int n, int* bestYear) {
    qsort(events, 2 * n, sizeof(struct Event), compare);
    int maxAlive = 0, currentAlive = 0;
    *bestYear = events[0].year;
    for (int i = 0; i < 2 * n; i++) {
        currentAlive += events[i].type;
        if (currentAlive > maxAlive) {
            maxAlive = currentAlive;
            *bestYear = events[i].year;
        }
    }
    return maxAlive;
}
int main() {
    struct Event events[] = {{1879, 1}, {1955, -1}, {1643, 1}, {1727, -1}};
    int bestYear;
    int maxCount = findBestTime(events, 2, &bestYear);
    printf("Best year: %d with %d scientists\n", bestYear, maxCount);
    return 0;
}
