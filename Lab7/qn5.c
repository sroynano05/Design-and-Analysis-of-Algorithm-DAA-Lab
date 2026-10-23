#include <stdio.h>
#include <stdbool.h>
bool huntTarget(int n) {
    int pos = 1;
    int step = 1;
    while (1) {
        printf("Shooting at spot: %d\n", pos);
        if (pos == n) step = -1;
        if (pos == 1) step = 1;
        pos += step;
    }
    return true;
}
int main() {
    int n = 5;
    return 0;
}
