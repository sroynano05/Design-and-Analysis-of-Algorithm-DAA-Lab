#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Symbol {
    char ch;
    int freq, len, code;
};
struct Node {
    int freq;
    char ch;
    struct Node *left, *right;
};
int compNode(const void* a, const void* b) {
    return (*(struct Node**)a)->freq - (*(struct Node**)b)->freq;
}
void getLengths(struct Node* root, int len, int lengths[]) {
    if (!root) return;
    if (!root->left && !root->right) { lengths[(unsigned char)root->ch] = len; return; }
    getLengths(root->left, len + 1, lengths);
    getLengths(root->right, len + 1, lengths);
}
int compCanonical(const void* a, const void* b) {
    struct Symbol* s1 = (struct Symbol*)a;
    struct Symbol* s2 = (struct Symbol*)b;
    if (s1->len != s2->len) return s1->len - s2->len;
    return s1->ch - s2->ch;
}
void canonicalHuffman(char chars[], int freqs[], int n) {
    struct Node* nodes[100];
    for (int i = 0; i < n; i++) {
        nodes[i] = malloc(sizeof(struct Node));
        nodes[i]->freq = freqs[i]; nodes[i]->ch = chars[i];
        nodes[i]->left = nodes[i]->right = NULL;
    }
    int size = n;
    while (size > 1) {
        qsort(nodes, size, sizeof(struct Node*), compNode);
        struct Node* parent = malloc(sizeof(struct Node));
        parent->freq = nodes[0]->freq + nodes[1]->freq;
        parent->ch = '\0'; parent->left = nodes[0]; parent->right = nodes[1];
        nodes[0] = parent;
        for (int i = 1; i < size - 1; i++) nodes[i] = nodes[i + 1];
        size--;
    }
    int lengths[256] = {0};
    getLengths(nodes[0], 0, lengths);
    struct Symbol syms[100];
    for (int i = 0; i < n; i++) {
        syms[i].ch = chars[i]; syms[i].freq = freqs[i]; syms[i].len = lengths[(unsigned char)chars[i]];
    }
    qsort(syms, n, sizeof(struct Symbol), compCanonical);
    int code = 0, currentLen = syms[0].len;
    for (int i = 0; i < n; i++) {
        code = code << (syms[i].len - currentLen);
        syms[i].code = code;
        currentLen = syms[i].len;
        code++;
        printf("Symbol %c: Length %d, Canonical Code: ", syms[i].ch, syms[i].len);
        for (int j = syms[i].len - 1; j >= 0; j--) printf("%d", (syms[i].code >> j) & 1);
        printf("\n");
    }
}
int main() {
    char chars[] = {'a', 'b', 'c', 'd'};
    int freqs[] = {5, 1, 6, 3};
    canonicalHuffman(chars, freqs, 4);
    return 0;
}
