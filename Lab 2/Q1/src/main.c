#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1000
#define STEP 50
#define TYPES 6
#define OPS 7
#define POINTS (MAXN / STEP)

const char *typeName[TYPES] = {
    "Unsorted Array", "Sorted Array", "Singly Unsorted",
    "Singly Sorted", "Doubly Unsorted", "Doubly Sorted"
};

const char *opName[OPS] = {
    "Search", "Insert", "Delete", "Maximum",
    "Minimum", "Predecessor", "Successor"
};

typedef struct SNode {
    int key;
    struct SNode *next;
} SNode;

typedef struct DNode {
    int key;
    struct DNode *prev;
    struct DNode *next;
} DNode;

long long count = 0;

void resetCount(void) {
    count = 0;
}

/* Unsorted Array */

int uaSearch(int a[], int n, int key) {
    int i;
    for (i = 0; i < n; i++) {
        count++;
        if (a[i] == key)
            return i;
    }
    return -1;
}

void uaInsert(int a[], int *n, int key) {
    a[*n] = key;
    (*n)++;
}

void uaDelete(int a[], int *n, int pos) {
    int i;
    for (i = pos; i < *n - 1; i++) {
        a[i] = a[i + 1];
        count++;
    }
    (*n)--;
}

int uaMin(int a[], int n) {
    int i, min = a[0];

    for (i = 1; i < n; i++) {
        count++;
        if (a[i] < min)
            min = a[i];
    }
    return min;
}

int uaMax(int a[], int n) {
    int i, max = a[0];

    for (i = 1; i < n; i++) {
        count++;
        if (a[i] > max)
            max = a[i];
    }
    return max;
}

int uaPred(int a[], int n, int key) {
    int i, pred = -1;

    for (i = 0; i < n; i++) {
        count++;
        if (a[i] < key && (pred == -1 || a[i] > pred))
            pred = a[i];
    }
    return pred;
}

int uaSucc(int a[], int n, int key) {
    int i, succ = -1;

    for (i = 0; i < n; i++) {
        count++;
        if (a[i] > key && (succ == -1 || a[i] < succ))
            succ = a[i];
    }
    return succ;
}

/* Sorted Array */

int saSearch(int a[], int n, int key) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        count++;

        if (a[mid] == key)
            return mid;

        count++;

        if (a[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

void saInsert(int a[], int *n, int key) {
    int i = *n - 1;

    while (i >= 0) {
        count++;

        if (a[i] > key) {
            a[i + 1] = a[i];
            i--;
        } else {
            break;
        }
    }

    a[i + 1] = key;
    (*n)++;
}

void saDelete(int a[], int *n, int pos) {
    int i;

    for (i = pos; i < *n - 1; i++) {
        a[i] = a[i + 1];
        count++;
    }

    (*n)--;
}

int saMin(int a[]) {
    return a[0];
}

int saMax(int a[], int n) {
    return a[n - 1];
}

int saPred(int pos) {
    return pos > 0 ? pos - 1 : -1;
}

int saSucc(int n, int pos) {
    return pos < n - 1 ? pos + 1 : -1;
}

/* Singly Linked Unsorted */

SNode *suInsert(SNode *head, int key) {
    SNode *node = (SNode *)malloc(sizeof(SNode));

    node->key = key;
    node->next = head;

    return node;
}

SNode *suSearch(SNode *head, int key) {
    while (head != NULL) {
        count++;

        if (head->key == key)
            return head;

        head = head->next;
    }

    return NULL;
}

void suDelete(SNode **head, SNode *target) {
    SNode *p;

    if (target == NULL)
        return;

    if (*head == target) {
        *head = target->next;
        free(target);
        return;
    }

    p = *head;

    while (p != NULL && p->next != target) {
        count++;
        p = p->next;
    }

    if (p != NULL)
        p->next = target->next;

    free(target);
}

int suMin(SNode *head) {
    int min = head->key;

    head = head->next;

    while (head != NULL) {
        count++;

        if (head->key < min)
            min = head->key;

        head = head->next;
    }

    return min;
}

int suMax(SNode *head) {
    int max = head->key;

    head = head->next;

    while (head != NULL) {
        count++;

        if (head->key > max)
            max = head->key;

        head = head->next;
    }

    return max;
}

int suPred(SNode *head, int key) {
    int pred = -1;

    while (head != NULL) {
        count++;

        if (head->key < key &&
            (pred == -1 || head->key > pred))
            pred = head->key;

        head = head->next;
    }

    return pred;
}

int suSucc(SNode *head, int key) {
    int succ = -1;

    while (head != NULL) {
        count++;

        if (head->key > key &&
            (succ == -1 || head->key < succ))
            succ = head->key;

        head = head->next;
    }

    return succ;
}

/* Singly Linked Sorted */

SNode *ssInsert(SNode *head, int key) {
    SNode *node = (SNode *)malloc(sizeof(SNode));
    SNode *p;

    node->key = key;
    node->next = NULL;

    if (head == NULL || head->key >= key) {
        node->next = head;
        return node;
    }

    p = head;

    while (p->next != NULL && p->next->key < key) {
        count++;
        p = p->next;
    }

    node->next = p->next;
    p->next = node;

    return head;
}

SNode *ssSearch(SNode *head, int key) {
    while (head != NULL) {
        count++;

        if (head->key == key)
            return head;

        if (head->key > key)
            return NULL;

        head = head->next;
    }

    return NULL;
}

void ssDelete(SNode **head, SNode *target) {
    SNode *p;

    if (target == NULL)
        return;

    if (*head == target) {
        *head = target->next;
        free(target);
        return;
    }

    p = *head;

    while (p != NULL && p->next != target) {
        count++;
        p = p->next;
    }

    if (p != NULL)
        p->next = target->next;

    free(target);
}

/* Doubly Linked Unsorted */

DNode *duInsert(DNode *head, int key) {
    DNode *node = (DNode *)malloc(sizeof(DNode));

    node->key = key;
    node->prev = NULL;
    node->next = head;

    if (head != NULL)
        head->prev = node;

    return node;
}

DNode *duSearch(DNode *head, int key) {
    while (head != NULL) {
        count++;

        if (head->key == key)
            return head;

        head = head->next;
    }

    return NULL;
}

void duDelete(DNode **head, DNode *target) {
    if (target == NULL)
        return;

    if (target->prev != NULL)
        target->prev->next = target->next;
    else
        *head = target->next;

    if (target->next != NULL)
        target->next->prev = target->prev;

    free(target);
}

int duMin(DNode *head) {
    int min = head->key;

    head = head->next;

    while (head != NULL) {
        count++;

        if (head->key < min)
            min = head->key;

        head = head->next;
    }

    return min;
}

int duMax(DNode *head) {
    int max = head->key;

    head = head->next;

    while (head != NULL) {
        count++;

        if (head->key > max)
            max = head->key;

        head = head->next;
    }

    return max;
}

int duPred(DNode *node) {
    if (node != NULL && node->prev != NULL)
        return node->prev->key;

    return -1;
}

int duSucc(DNode *node) {
    if (node != NULL && node->next != NULL)
        return node->next->key;

    return -1;
}

/* Doubly Linked Sorted */

DNode *dsInsert(DNode *head, int key) {
    DNode *node = (DNode *)malloc(sizeof(DNode));
    DNode *p;

    node->key = key;
    node->prev = NULL;
    node->next = NULL;

    if (head == NULL)
        return node;

    if (key <= head->key) {
        node->next = head;
        head->prev = node;
        return node;
    }

    p = head;

    while (p->next != NULL && p->next->key < key) {
        count++;
        p = p->next;
    }

    node->next = p->next;
    node->prev = p;

    if (p->next != NULL)
        p->next->prev = node;

    p->next = node;

    return head;
}

void freeSList(SNode *head) {
    SNode *next;

    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    }
}

void freeDList(DNode *head) {
    DNode *next;

    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    }
}

/* Measurement */

long long runOperation(int type, int op, int n) {
    int *a;
    int *b;

    SNode *su = NULL;
    SNode *ss = NULL;

    DNode *du = NULL;
    DNode *ds = NULL;

    int i;

    a = (int *)malloc((MAXN + 2) * sizeof(int));
    b = (int *)malloc((MAXN + 2) * sizeof(int));

    for (i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i;

        su = suInsert(su, i);
        ss = ssInsert(ss, i);

        du = duInsert(du, i);
        ds = dsInsert(ds, i);
    }

    resetCount();

    if (type == 0) {
        if (op == 0)
            uaSearch(a, n, -1);
        else if (op == 1) {
            int m = n;
            uaInsert(a, &m, n);
        }
        else if (op == 2) {
            int m = n;
            uaDelete(a, &m, n / 2);
        }
        else if (op == 3)
            uaMax(a, n);
        else if (op == 4)
            uaMin(a, n);
        else if (op == 5)
            uaPred(a, n, n / 2);
        else
            uaSucc(a, n, n / 2);
    }
    else if (type == 1) {
        if (op == 0)
            saSearch(b, n, -1);
        else if (op == 1) {
            int m = n;
            saInsert(b, &m, n / 2);
        }
        else if (op == 2) {
            int m = n;
            saDelete(b, &m, n / 2);
        }
        else if (op == 3)
            saMax(b, n);
        else if (op == 4)
            saMin(b);
        else if (op == 5)
            saPred(n / 2);
        else
            saSucc(n, n / 2);
    }
    else if (type == 2) {
        if (op == 0)
            suSearch(su, -1);
        else if (op == 1)
            su = suInsert(su, n);
        else if (op == 2) {
            SNode *x = suSearch(su, n / 2);
            resetCount();
            suDelete(&su, x);
        }
        else if (op == 3)
            suMax(su);
        else if (op == 4)
            suMin(su);
        else if (op == 5)
            suPred(su, n / 2);
        else
            suSucc(su, n / 2);
    }
    else if (type == 3) {
        if (op == 0)
            ssSearch(ss, -1);
        else if (op == 1)
            ss = ssInsert(ss, n);
        else if (op == 2) {
            SNode *x = ssSearch(ss, n / 2);
            resetCount();
            ssDelete(&ss, x);
        }
        else if (op == 3) {
            SNode *p = ss;
            while (p->next != NULL) {
                count++;
                p = p->next;
            }
        }
        else if (op == 4)
            count = 1;
        else if (op == 5 || op == 6) {
            SNode *p = ss;
            for (i = 0; i < n / 2; i++) {
                count++;
                p = p->next;
            }
        }
    }
    else if (type == 4) {
        if (op == 0)
            duSearch(du, -1);
        else if (op == 1)
            du = duInsert(du, n);
        else if (op == 2) {
            DNode *x = duSearch(du, n / 2);
            resetCount();
            duDelete(&du, x);
        }
        else if (op == 3)
            duMax(du);
        else if (op == 4)
            duMin(du);
        else {
            DNode *x = duSearch(du, n / 2);
            resetCount();

            if (op == 5)
                duPred(x);
            else
                duSucc(x);
        }
    }
    else {
        if (op == 0)
            duSearch(ds, -1);
        else if (op == 1)
            ds = dsInsert(ds, n);
        else if (op == 2) {
            DNode *x = duSearch(ds, n / 2);
            resetCount();
            duDelete(&ds, x);
        }
        else if (op == 3 || op == 4)
            count = 1;
        else {
            DNode *x = duSearch(ds, n / 2);
            resetCount();

            if (op == 5)
                duPred(x);
            else
                duSucc(x);
        }
    }

    if (count < 1)
        count = 1;

    {
        long long result = count;

        free(a);
        free(b);

        freeSList(su);
        freeSList(ss);
        freeDList(du);
        freeDList(ds);

        return result;
    }
}

/* Raylib Graph */

int main(void) {
    int operation = 0;
    double values[TYPES][POINTS];

    InitWindow(1200, 750, "Dictionary Operations - Raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        int t, i;
        double maxValue = 1;

        if (IsKeyPressed(KEY_RIGHT))
            operation = (operation + 1) % OPS;

        if (IsKeyPressed(KEY_LEFT))
            operation = (operation + OPS - 1) % OPS;

        for (t = 0; t < TYPES; t++) {
            for (i = 0; i < POINTS; i++) {
                values[t][i] =
                    (double)runOperation(t, operation, (i + 1) * STEP);

                if (values[t][i] > maxValue)
                    maxValue = values[t][i];
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Dictionary Operations", 30, 20, 30, BLACK);

        DrawText(
            TextFormat(
                "Operation: %s   |   LEFT / RIGHT to change",
                opName[operation]
            ),
            30, 58, 20, DARKGRAY
        );

        {
            int gx = 80;
            int gy = 110;
            int gw = 1050;
            int gh = 500;

            DrawLine(gx, gy + gh, gx + gw, gy + gh, BLACK);
            DrawLine(gx, gy, gx, gy + gh, BLACK);

            for (i = 0; i <= 10; i++) {
                int x = gx + i * gw / 10;

                DrawLine(x, gy + gh, x, gy + gh + 5, GRAY);

                DrawText(
                    TextFormat("%d", i * 100),
                    x - 15, gy + gh + 10, 14, DARKGRAY
                );
            }

            for (i = 1; i <= 5; i++) {
                int y = gy + gh - i * gh / 5;

                DrawLine(gx - 5, y, gx, y, GRAY);

                DrawText(
                    TextFormat("%.0f", maxValue * i / 5),
                    gx - 65, y - 8, 12, DARKGRAY
                );
            }

            for (t = 0; t < TYPES; t++) {
                Color c = {
                    (unsigned char)((t * 43 + 30) % 255),
                    (unsigned char)((t * 79 + 80) % 255),
                    (unsigned char)((t * 117 + 120) % 255),
                    255
                };

                for (i = 1; i < POINTS; i++) {
                    float x1 =
                        gx + (i - 1) * gw / (float)(POINTS - 1);
                    float x2 =
                        gx + i * gw / (float)(POINTS - 1);

                    float y1 =
                        gy + gh -
                        (float)(values[t][i - 1] / maxValue) * gh;

                    float y2 =
                        gy + gh -
                        (float)(values[t][i] / maxValue) * gh;

                    DrawLineEx(
                        (Vector2){x1, y1},
                        (Vector2){x2, y2},
                        2,
                        c
                    );
                }

                {
                    int lx = 70 + (t % 3) * 370;
                    int ly = 650 + (t / 3) * 25;

                    DrawRectangle(lx, ly + 5, 20, 4, c);
                    DrawText(
                        typeName[t],
                        lx + 28, ly, 15, BLACK
                    );
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}