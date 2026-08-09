#include "raylib.h"
#include <stdlib.h>
#define MAX_N 1000
#define STEP 50
#define POINTS (MAX_N / STEP)
#define DS 6
#define OPS 7

typedef struct {
    int key;
    int value;
} Element;

typedef struct SNode {
    Element data;
    struct SNode *next;
} SNode;

typedef struct DNode {
    Element data;
    struct DNode *prev;
    struct DNode *next;
} DNode;

long long operations;

/* ---------- Unsorted Array ---------- */

typedef struct {
    Element *a;
    int n;
} UnsortedArray;

UnsortedArray createUnsortedArray(int n) {
    UnsortedArray d;
    int i;

    d.n = n;
    d.a = (Element *)malloc(n * sizeof(Element));

    for (i = 0; i < n; i++) {
        d.a[i].key = n - i;
        d.a[i].value = d.a[i].key * 10;
    }

    return d;
}

void destroyUnsortedArray(UnsortedArray *d) {
    free(d->a);
    d->a = NULL;
    d->n = 0;
}

int unsortedSearch(UnsortedArray *d, int key) {
    int i;

    for (i = 0; i < d->n; i++) {
        operations++;

        if (d->a[i].key == key)
            return i;
    }

    return -1;
}

void unsortedInsert(UnsortedArray *d, Element x) {
    Element *b;
    int i;

    b = (Element *)malloc((d->n + 1) * sizeof(Element));

    for (i = 0; i < d->n; i++)
        b[i] = d->a[i];

    b[d->n] = x;

    free(d->a);
    d->a = b;
    d->n++;
}

void unsortedDelete(UnsortedArray *d, int index) {
    int i;

    if (index < 0 || index >= d->n)
        return;

    for (i = index; i < d->n - 1; i++) {
        operations++;
        d->a[i] = d->a[i + 1];
    }

    d->n--;
}

int unsortedMaximum(UnsortedArray *d) {
    int p = 0;
    int i;

    for (i = 1; i < d->n; i++) {
        operations++;

        if (d->a[i].key > d->a[p].key)
            p = i;
    }

    return p;
}

int unsortedMinimum(UnsortedArray *d) {
    int p = 0;
    int i;

    for (i = 1; i < d->n; i++) {
        operations++;

        if (d->a[i].key < d->a[p].key)
            p = i;
    }

    return p;
}

int unsortedPredecessor(UnsortedArray *d, int index) {
    int p = -1;
    int i;
    int key;

    if (index < 0 || index >= d->n)
        return -1;

    key = d->a[index].key;

    for (i = 0; i < d->n; i++) {
        operations++;

        if (d->a[i].key < key &&
            (p == -1 || d->a[i].key > d->a[p].key))
            p = i;
    }

    return p;
}

int unsortedSuccessor(UnsortedArray *d, int index) {
    int p = -1;
    int i;
    int key;

    if (index < 0 || index >= d->n)
        return -1;

    key = d->a[index].key;

    for (i = 0; i < d->n; i++) {
        operations++;

        if (d->a[i].key > key &&
            (p == -1 || d->a[i].key < d->a[p].key))
            p = i;
    }

    return p;
}

/* ---------- Sorted Array ---------- */

typedef struct {
    Element *a;
    int n;
} SortedArray;

SortedArray createSortedArray(int n) {
    SortedArray d;
    int i;

    d.n = n;
    d.a = (Element *)malloc(n * sizeof(Element));

    for (i = 0; i < n; i++) {
        d.a[i].key = i + 1;
        d.a[i].value = (i + 1) * 10;
    }

    return d;
}

void destroySortedArray(SortedArray *d) {
    free(d->a);
    d->a = NULL;
    d->n = 0;
}

int sortedSearch(SortedArray *d, int key) {
    int left = 0;
    int right = d->n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        operations++;

        if (d->a[mid].key == key)
            return mid;

        if (d->a[mid].key < key)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

void sortedInsert(SortedArray *d, Element x) {
    Element *b;
    int i;
    int j;

    b = (Element *)malloc((d->n + 1) * sizeof(Element));

    i = d->n - 1;

    while (i >= 0 && d->a[i].key > x.key) {
        operations++;
        b[i + 1] = d->a[i];
        i--;
    }

    b[i + 1] = x;

    for (j = 0; j <= i; j++)
        b[j] = d->a[j];

    free(d->a);
    d->a = b;
    d->n++;
}

void sortedDelete(SortedArray *d, int index) {
    int i;

    if (index < 0 || index >= d->n)
        return;

    for (i = index; i < d->n - 1; i++) {
        operations++;
        d->a[i] = d->a[i + 1];
    }

    d->n--;
}

int sortedMaximum(SortedArray *d) {
    return d->n - 1;
}

int sortedMinimum(SortedArray *d) {
    return 0;
}

int sortedPredecessor(SortedArray *d, int index) {
    if (index <= 0 || index >= d->n)
        return -1;

    return index - 1;
}

int sortedSuccessor(SortedArray *d, int index) {
    if (index < 0 || index >= d->n - 1)
        return -1;

    return index + 1;
}

/* ---------- Singly Linked Unsorted ---------- */

typedef struct {
    SNode *head;
    int n;
} SinglyUnsorted;

SinglyUnsorted createSinglyUnsorted(int n) {
    SinglyUnsorted d;
    int i;

    d.head = NULL;
    d.n = n;

    for (i = 0; i < n; i++) {
        SNode *p = (SNode *)malloc(sizeof(SNode));

        p->data.key = i + 1;
        p->data.value = (i + 1) * 10;
        p->next = d.head;
        d.head = p;
    }

    return d;
}

void destroySinglyUnsorted(SinglyUnsorted *d) {
    while (d->head != NULL) {
        SNode *p = d->head;
        d->head = d->head->next;
        free(p);
    }

    d->n = 0;
}

SNode *singlyUnsortedSearch(SinglyUnsorted *d, int key) {
    SNode *p = d->head;

    while (p != NULL) {
        operations++;

        if (p->data.key == key)
            return p;

        p = p->next;
    }

    return NULL;
}

void singlyUnsortedInsert(SinglyUnsorted *d, Element x) {
    SNode *p = (SNode *)malloc(sizeof(SNode));

    p->data = x;
    p->next = d->head;
    d->head = p;
    d->n++;
}

void singlyUnsortedDelete(SinglyUnsorted *d, SNode *x) {
    SNode *p;

    if (x == NULL || d->head == NULL)
        return;

    if (x == d->head) {
        d->head = d->head->next;
        free(x);
        d->n--;
        return;
    }

    p = d->head;

    while (p->next != x) {
        operations++;
        p = p->next;
    }

    p->next = x->next;
    free(x);
    d->n--;
}

SNode *singlyUnsortedMaximum(SinglyUnsorted *d) {
    SNode *best = d->head;
    SNode *p;

    if (best == NULL)
        return NULL;

    p = best->next;

    while (p != NULL) {
        operations++;

        if (p->data.key > best->data.key)
            best = p;

        p = p->next;
    }

    return best;
}

SNode *singlyUnsortedMinimum(SinglyUnsorted *d) {
    SNode *best = d->head;
    SNode *p;

    if (best == NULL)
        return NULL;

    p = best->next;

    while (p != NULL) {
        operations++;

        if (p->data.key < best->data.key)
            best = p;

        p = p->next;
    }

    return best;
}

SNode *singlyUnsortedPredecessor(SinglyUnsorted *d, SNode *x) {
    SNode *best = NULL;
    SNode *p;

    if (x == NULL)
        return NULL;

    p = d->head;

    while (p != NULL) {
        operations++;

        if (p->data.key < x->data.key &&
            (best == NULL || p->data.key > best->data.key))
            best = p;

        p = p->next;
    }

    return best;
}

SNode *singlyUnsortedSuccessor(SinglyUnsorted *d, SNode *x) {
    SNode *best = NULL;
    SNode *p;

    if (x == NULL)
        return NULL;

    p = d->head;

    while (p != NULL) {
        operations++;

        if (p->data.key > x->data.key &&
            (best == NULL || p->data.key < best->data.key))
            best = p;

        p = p->next;
    }

    return best;
}

/* ---------- Singly Linked Sorted ---------- */

typedef struct {
    SNode *head;
    int n;
} SinglySorted;

SinglySorted createSinglySorted(int n) {
    SinglySorted d;
    int i;

    d.head = NULL;
    d.n = n;

    for (i = n; i >= 1; i--) {
        SNode *p = (SNode *)malloc(sizeof(SNode));

        p->data.key = i;
        p->data.value = i * 10;
        p->next = d.head;
        d.head = p;
    }

    return d;
}

void destroySinglySorted(SinglySorted *d) {
    while (d->head != NULL) {
        SNode *p = d->head;
        d->head = d->head->next;
        free(p);
    }

    d->n = 0;
}

SNode *singlySortedSearch(SinglySorted *d, int key) {
    SNode *p = d->head;

    while (p != NULL) {
        operations++;

        if (p->data.key == key)
            return p;

        if (p->data.key > key)
            return NULL;

        p = p->next;
    }

    return NULL;
}

void singlySortedInsert(SinglySorted *d, Element x) {
    SNode *p;
    SNode *q;

    p = (SNode *)malloc(sizeof(SNode));
    p->data = x;
    p->next = NULL;

    if (d->head == NULL || x.key < d->head->data.key) {
        p->next = d->head;
        d->head = p;
        d->n++;
        return;
    }

    q = d->head;

    while (q->next != NULL && q->next->data.key < x.key) {
        operations++;
        q = q->next;
    }

    p->next = q->next;
    q->next = p;
    d->n++;
}

void singlySortedDelete(SinglySorted *d, SNode *x) {
    SNode *p;

    if (x == NULL || d->head == NULL)
        return;

    if (x == d->head) {
        d->head = d->head->next;
        free(x);
        d->n--;
        return;
    }

    p = d->head;

    while (p->next != x) {
        operations++;
        p = p->next;
    }

    p->next = x->next;
    free(x);
    d->n--;
}

SNode *singlySortedMaximum(SinglySorted *d) {
    SNode *p = d->head;

    if (p == NULL)
        return NULL;

    while (p->next != NULL) {
        operations++;
        p = p->next;
    }

    return p;
}

SNode *singlySortedMinimum(SinglySorted *d) {
    return d->head;
}

SNode *singlySortedPredecessor(SNode *x, SNode *head) {
    SNode *p;

    if (x == NULL || x == head)
        return NULL;

    p = head;

    while (p->next != x) {
        operations++;
        p = p->next;
    }

    return p;
}

SNode *singlySortedSuccessor(SNode *x) {
    if (x == NULL)
        return NULL;

    return x->next;
}

/* ---------- Doubly Linked Unsorted ---------- */

typedef struct {
    DNode *head;
    DNode *tail;
    int n;
} DoublyUnsorted;

DoublyUnsorted createDoublyUnsorted(int n) {
    DoublyUnsorted d;
    int i;

    d.head = NULL;
    d.tail = NULL;
    d.n = n;

    for (i = 1; i <= n; i++) {
        DNode *p = (DNode *)malloc(sizeof(DNode));

        p->data.key = i;
        p->data.value = i * 10;
        p->prev = d.tail;
        p->next = NULL;

        if (d.tail != NULL)
            d.tail->next = p;
        else
            d.head = p;

        d.tail = p;
    }

    return d;
}

void destroyDoublyUnsorted(DoublyUnsorted *d) {
    while (d->head != NULL) {
        DNode *p = d->head;
        d->head = d->head->next;
        free(p);
    }

    d->tail = NULL;
    d->n = 0;
}

DNode *doublyUnsortedSearch(DoublyUnsorted *d, int key) {
    DNode *p = d->head;

    while (p != NULL) {
        operations++;

        if (p->data.key == key)
            return p;

        p = p->next;
    }

    return NULL;
}

void doublyUnsortedInsert(DoublyUnsorted *d, Element x) {
    DNode *p = (DNode *)malloc(sizeof(DNode));

    p->data = x;
    p->next = d->head;
    p->prev = NULL;

    if (d->head != NULL)
        d->head->prev = p;
    else
        d->tail = p;

    d->head = p;
    d->n++;
}

void doublyUnsortedDelete(DoublyUnsorted *d, DNode *x) {
    if (x == NULL)
        return;

    if (x->prev != NULL)
        x->prev->next = x->next;
    else
        d->head = x->next;

    if (x->next != NULL)
        x->next->prev = x->prev;
    else
        d->tail = x->prev;

    free(x);
    d->n--;
}

DNode *doublyUnsortedMaximum(DoublyUnsorted *d) {
    DNode *best = d->head;
    DNode *p;

    if (best == NULL)
        return NULL;

    p = best->next;

    while (p != NULL) {
        operations++;

        if (p->data.key > best->data.key)
            best = p;

        p = p->next;
    }

    return best;
}

DNode *doublyUnsortedMinimum(DoublyUnsorted *d) {
    DNode *best = d->head;
    DNode *p;

    if (best == NULL)
        return NULL;

    p = best->next;

    while (p != NULL) {
        operations++;

        if (p->data.key < best->data.key)
            best = p;

        p = p->next;
    }

    return best;
}

DNode *doublyUnsortedPredecessor(DNode *x) {
    if (x == NULL)
        return NULL;

    return x->prev;
}

DNode *doublyUnsortedSuccessor(DNode *x) {
    if (x == NULL)
        return NULL;

    return x->next;
}

/* ---------- Doubly Linked Sorted ---------- */

typedef struct {
    DNode *head;
    DNode *tail;
    int n;
} DoublySorted;

DoublySorted createDoublySorted(int n) {
    DoublySorted d;
    int i;

    d.head = NULL;
    d.tail = NULL;
    d.n = n;

    for (i = 1; i <= n; i++) {
        DNode *p = (DNode *)malloc(sizeof(DNode));

        p->data.key = i;
        p->data.value = i * 10;
        p->prev = d.tail;
        p->next = NULL;

        if (d.tail != NULL)
            d.tail->next = p;
        else
            d.head = p;

        d.tail = p;
    }

    return d;
}

void destroyDoublySorted(DoublySorted *d) {
    while (d->head != NULL) {
        DNode *p = d->head;
        d->head = d->head->next;
        free(p);
    }

    d->tail = NULL;
    d->n = 0;
}

DNode *doublySortedSearch(DoublySorted *d, int key) {
    DNode *p = d->head;

    while (p != NULL) {
        operations++;

        if (p->data.key == key)
            return p;

        if (p->data.key > key)
            return NULL;

        p = p->next;
    }

    return NULL;
}

void doublySortedInsert(DoublySorted *d, Element x) {
    DNode *p;
    DNode *q;

    p = (DNode *)malloc(sizeof(DNode));
    p->data = x;

    if (d->head == NULL) {
        p->prev = NULL;
        p->next = NULL;
        d->head = d->tail = p;
        d->n++;
        return;
    }

    if (x.key < d->head->data.key) {
        p->prev = NULL;
        p->next = d->head;
        d->head->prev = p;
        d->head = p;
        d->n++;
        return;
    }

    q = d->head;

    while (q->next != NULL && q->next->data.key < x.key) {
        operations++;
        q = q->next;
    }

    p->prev = q;
    p->next = q->next;

    if (q->next != NULL)
        q->next->prev = p;
    else
        d->tail = p;

    q->next = p;
    d->n++;
}

void doublySortedDelete(DoublySorted *d, DNode *x) {
    if (x == NULL)
        return;

    if (x->prev != NULL)
        x->prev->next = x->next;
    else
        d->head = x->next;

    if (x->next != NULL)
        x->next->prev = x->prev;
    else
        d->tail = x->prev;

    free(x);
    d->n--;
}

DNode *doublySortedMaximum(DoublySorted *d) {
    return d->tail;
}

DNode *doublySortedMinimum(DoublySorted *d) {
    return d->head;
}

DNode *doublySortedPredecessor(DNode *x) {
    if (x == NULL)
        return NULL;

    return x->prev;
}

DNode *doublySortedSuccessor(DNode *x) {
    if (x == NULL)
        return NULL;

    return x->next;
}

/* ---------- Measurement ---------- */

long long measure(int ds, int operation, int n) {
    int key = n;

    operations = 0;

    if (ds == 0) {
        UnsortedArray d = createUnsortedArray(n);
        int index = unsortedSearch(&d, key);

        /*
         * Search above is only used to obtain x for operations
         * that require a pointer/index. Reset the counter so it
         * is not included in those operations.
         */
        operations = 0;

        if (operation == 0)
            unsortedSearch(&d, key);
        else if (operation == 1)
            unsortedInsert(&d, (Element){n + 1, (n + 1) * 10});
        else if (operation == 2)
            unsortedDelete(&d, index);
        else if (operation == 3)
            unsortedMaximum(&d);
        else if (operation == 4)
            unsortedMinimum(&d);
        else if (operation == 5)
            unsortedPredecessor(&d, index);
        else
            unsortedSuccessor(&d, index);

        destroyUnsortedArray(&d);
    }

    else if (ds == 1) {
        SortedArray d = createSortedArray(n);
        int index = sortedSearch(&d, key);

        operations = 0;

        if (operation == 0)
            sortedSearch(&d, key);
        else if (operation == 1)
            sortedInsert(&d, (Element){n + 1, (n + 1) * 10});
        else if (operation == 2)
            sortedDelete(&d, index);
        else if (operation == 3)
            sortedMaximum(&d);
        else if (operation == 4)
            sortedMinimum(&d);
        else if (operation == 5)
            sortedPredecessor(&d, index);
        else
            sortedSuccessor(&d, index);

        destroySortedArray(&d);
    }

    else if (ds == 2) {
        SinglyUnsorted d = createSinglyUnsorted(n);
        SNode *x = singlyUnsortedSearch(&d, key);

        operations = 0;

        if (operation == 0)
            singlyUnsortedSearch(&d, key);
        else if (operation == 1)
            singlyUnsortedInsert(&d, (Element){n + 1, (n + 1) * 10});
        else if (operation == 2)
            singlyUnsortedDelete(&d, x);
        else if (operation == 3)
            singlyUnsortedMaximum(&d);
        else if (operation == 4)
            singlyUnsortedMinimum(&d);
        else if (operation == 5)
            singlyUnsortedPredecessor(&d, x);
        else
            singlyUnsortedSuccessor(&d, x);

        destroySinglyUnsorted(&d);
    }

    else if (ds == 3) {
        SinglySorted d = createSinglySorted(n);
        SNode *x = singlySortedSearch(&d, key);

        operations = 0;

        if (operation == 0)
            singlySortedSearch(&d, key);
        else if (operation == 1)
            singlySortedInsert(&d, (Element){n + 1, (n + 1) * 10});
        else if (operation == 2)
            singlySortedDelete(&d, x);
        else if (operation == 3)
            singlySortedMaximum(&d);
        else if (operation == 4)
            singlySortedMinimum(&d);
        else if (operation == 5)
            singlySortedPredecessor(x, d.head);
        else
            singlySortedSuccessor(x);

        destroySinglySorted(&d);
    }

    else if (ds == 4) {
        DoublyUnsorted d = createDoublyUnsorted(n);
        DNode *x = doublyUnsortedSearch(&d, key);

        operations = 0;

        if (operation == 0)
            doublyUnsortedSearch(&d, key);
        else if (operation == 1)
            doublyUnsortedInsert(&d, (Element){n + 1, (n + 1) * 10});
        else if (operation == 2)
            doublyUnsortedDelete(&d, x);
        else if (operation == 3)
            doublyUnsortedMaximum(&d);
        else if (operation == 4)
            doublyUnsortedMinimum(&d);
        else if (operation == 5)
            doublyUnsortedPredecessor(x);
        else
            doublyUnsortedSuccessor(x);

        destroyDoublyUnsorted(&d);
    }

    else {
        DoublySorted d = createDoublySorted(n);
        DNode *x = doublySortedSearch(&d, key);

        operations = 0;

        if (operation == 0)
            doublySortedSearch(&d, key);
        else if (operation == 1)
            doublySortedInsert(&d, (Element){n + 1, (n + 1) * 10});
        else if (operation == 2)
            doublySortedDelete(&d, x);
        else if (operation == 3)
            doublySortedMaximum(&d);
        else if (operation == 4)
            doublySortedMinimum(&d);
        else if (operation == 5)
            doublySortedPredecessor(x);
        else
            doublySortedSuccessor(x);

        destroyDoublySorted(&d);
    }

    return operations;
}

/* ---------- Raylib ---------- */

int main(void) {
    const char *dsNames[DS] = {
        "Unsorted Array",
        "Sorted Array",
        "Singly Linked Unsorted",
        "Singly Linked Sorted",
        "Doubly Linked Unsorted",
        "Doubly Linked Sorted"
    };

    const char *opNames[OPS] = {
        "Search",
        "Insert",
        "Delete",
        "Maximum",
        "Minimum",
        "Predecessor",
        "Successor"
    };

    double graph[DS][POINTS];
    int currentOperation = 0;
    int ds;
    int i;

    Color colors[DS] = {
        BLUE,
        RED,
        GREEN,
        ORANGE,
        PURPLE,
        MAROON
    };

    /*
     * Generate all graph data before opening the window.
     */
    for (currentOperation = 0; currentOperation < OPS; currentOperation++) {
        for (ds = 0; ds < DS; ds++) {
            for (i = 0; i < POINTS; i++) {
                int n = (i + 1) * STEP;

                graph[ds][i] =
                    (double)measure(ds, currentOperation, n);
            }
        }
    }

    currentOperation = 0;

    InitWindow(
        1250,
        800,
        "Dictionary Operations - DAA Lab 02"
    );

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        double maxValue = 1.0;

        if (IsKeyPressed(KEY_RIGHT))
            currentOperation =
                (currentOperation + 1) % OPS;

        if (IsKeyPressed(KEY_LEFT))
            currentOperation =
                (currentOperation - 1 + OPS) % OPS;

        for (ds = 0; ds < DS; ds++) {
            for (i = 0; i < POINTS; i++) {
                if (graph[ds][i] > maxValue)
                    maxValue = graph[ds][i];
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(
            "Dictionary Operations",
            30, 20, 32, BLACK
        );

        DrawText(
            TextFormat(
                "Operation: %s    [LEFT / RIGHT to change]",
                opNames[currentOperation]
            ),
            30, 60, 22, DARKGRAY
        );

        {
            int gx = 100;
            int gy = 120;
            int gw = 1050;
            int gh = 500;

            DrawLine(
                gx, gy,
                gx, gy + gh,
                BLACK
            );

            DrawLine(
                gx, gy + gh,
                gx + gw, gy + gh,
                BLACK
            );

            for (i = 0; i <= 10; i++) {
                int x = gx + i * gw / 10;

                DrawLine(
                    x, gy + gh,
                    x, gy + gh + 5,
                    GRAY
                );

                DrawText(
                    TextFormat(
                        "%d",
                        i * MAX_N / 10
                    ),
                    x - 15,
                    gy + gh + 10,
                    14,
                    DARKGRAY
                );
            }

            for (i = 1; i <= 5; i++) {
                int y = gy + gh - i * gh / 5;

                DrawLine(
                    gx - 5, y,
                    gx, y,
                    GRAY
                );

                DrawText(
                    TextFormat(
                        "%.0f",
                        maxValue * i / 5
                    ),
                    gx - 75,
                    y - 8,
                    12,
                    DARKGRAY
                );
            }

            for (ds = 0; ds < DS; ds++) {
                for (i = 1; i < POINTS; i++) {
                    float x1 =
                        gx +
                        (i - 1) * gw /
                        (float)(POINTS - 1);

                    float x2 =
                        gx +
                        i * gw /
                        (float)(POINTS - 1);

                    float y1 =
                        gy + gh -
                        (float)(
                            graph[ds][i - 1] /
                            maxValue
                        ) * gh;

                    float y2 =
                        gy + gh -
                        (float)(
                            graph[ds][i] /
                            maxValue
                        ) * gh;

                    DrawLineEx(
                        (Vector2){x1, y1},
                        (Vector2){x2, y2},
                        2,
                        colors[ds]
                    );
                }
            }
        }

        {
            int lx = 120;
            int ly = 660;

            for (ds = 0; ds < DS; ds++) {
                int row = ds / 3;
                int col = ds % 3;

                int x = lx + col * 350;
                int y = ly + row * 35;

                DrawRectangle(
                    x,
                    y + 5,
                    20,
                    5,
                    colors[ds]
                );

                DrawText(
                    dsNames[ds],
                    x + 30,
                    y,
                    16,
                    BLACK
                );
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}