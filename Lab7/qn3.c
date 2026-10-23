#include <stdio.h>
#include <math.h>
void hanoi3(int n, char from, char to, char aux) {
    if (n == 0) return;
    hanoi3(n - 1, from, aux, to);
    printf("Move disk %d from %c to %c\n", n, from, to);
    hanoi3(n - 1, aux, to, from);
}
void revesPuzzle(int n, char from, char to, char aux1, char aux2) {
    if (n == 0) return;
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", from, to);
        return;
    }
    int k = n + 1 - round(sqrt(2 * n + 1)); 
    revesPuzzle(k, from, aux1, aux2, to);
    hanoi3(n - k, from, to, aux2);
    revesPuzzle(k, aux1, to, from, aux2);
}
int main() {
    int disks = 8;
    revesPuzzle(disks, 'A', 'D', 'B', 'C');
    return 0;
}
