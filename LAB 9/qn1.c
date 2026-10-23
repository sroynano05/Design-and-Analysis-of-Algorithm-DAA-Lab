#include <stdio.h>
#include <stdlib.h>
struct Item {
    double v, w, lambda;
};
int compareItems(const void* a, const void* b) {
    struct Item* i1 = (struct Item*)a;
    struct Item* i2 = (struct Item*)b;
    double ratio1 = (i1->v / i1->w) / i1->lambda;
    double ratio2 = (i2->v / i2->w) / i2->lambda;
    if (ratio1 < ratio2) return 1;
    if (ratio1 > ratio2) return -1;
    return 0;
}
double maxKnapsackValue(struct Item items[], int n, double W) {
    qsort(items, n, sizeof(struct Item), compareItems);
    double totalValue = 0.0, currentWeight = 0.0, t = 0.0;
    for (int i = 0; i < n; i++) {
        if (currentWeight + items[i].w <= W) {
            double effDensity = (items[i].v / items[i].w) - items[i].lambda * t;
            if (effDensity > 0) totalValue += effDensity * items[i].w;
            t += items[i].w;
            currentWeight += items[i].w;
        } else {
            double remain = W - currentWeight;
            double effDensity = (items[i].v / items[i].w) - items[i].lambda * t;
            if (effDensity > 0) totalValue += effDensity * remain;
            break;
        }
    }
    return totalValue;
}
int main() {
    struct Item items[] = {{60, 10, 0.1}, {100, 20, 0.2}, {120, 30, 0.15}};
    printf("Max value: %.2f\n", maxKnapsackValue(items, 3, 50));
    return 0;
}
