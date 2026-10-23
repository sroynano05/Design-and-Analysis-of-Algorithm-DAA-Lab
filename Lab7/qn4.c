#include <stdio.h>
void toggle(int i, int n) {
    printf("Toggle switch %d\n", i);
}
void turnOff(int n, int direction) {
    if (n == 0) return;
    if (direction) {
        turnOff(n - 1, 1);
        toggle(n, n);
        turnOff(n - 1, 0);
    } else {
        turnOff(n - 1, 1);
        toggle(n, n);
        turnOff(n - 1, 0);
    }
}

int main() {
    int n = 3;
    turnOff(n, 1);
    return 0;
}

