#include <stdio.h>
#include <string.h>

struct Key {
    char ch; int freq;
};

void maxHeapify(struct Key heap[], int size, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < size && heap[left].freq > heap[largest].freq) largest = left;
    if (right < size && heap[right].freq > heap[largest].freq) largest = right;
    if (largest != i) {
        struct Key tmp = heap[i]; heap[i] = heap[largest]; heap[largest] = tmp;
        maxHeapify(heap, size, largest);
    }
}

void rearrangeString(char str[], int k, char result[]) {
    int count[26] = {0}, n = strlen(str);
    for (int i = 0; i < n; i++) count[str[i] - 'a']++;
    struct Key heap[26]; int heapSize = 0;
    for (int i = 0; i < 26; i++) {
        if (count[i] > 0) { heap[heapSize].ch = 'a' + i; heap[heapSize].freq = count[i]; heapSize++; }
    }
    for (int i = heapSize / 2 - 1; i >= 0; i--) maxHeapify(heap, heapSize, i);
    struct Key queue[26]; int head = 0, tail = 0;
    int idx = 0;
    while (heapSize > 0) {
        struct Key curr = heap[0];
        heap[0] = heap[--heapSize];
        maxHeapify(heap, heapSize, 0);
        result[idx++] = curr.ch;
        curr.freq--;
        queue[tail++] = curr;
        if (tail - head >= k) {
            struct Key ready = queue[head++];
            if (ready.freq > 0) {
                heap[heapSize++] = ready;
                int c = heapSize - 1;
                while (c > 0 && heap[c].freq > heap[(c - 1) / 2].freq) {
                    struct Key tmp = heap[c]; heap[c] = heap[(c - 1) / 2]; heap[(c - 1) / 2] = tmp;
                    c = (c - 1) / 2;
                }
            }
        }
    }
    result[idx] = '\0';
    if (idx != n) strcpy(result, "");
}

int main() {
    char str[] = "aabbcc", res[100];
    rearrangeString(str, 3, res);
    printf("Result: %s\n", res);
    return 0;
}

