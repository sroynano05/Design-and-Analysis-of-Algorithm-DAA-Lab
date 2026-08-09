#include "raylib.h"
#include <stdlib.h>

#define MAX_N 1500
#define STEP 50
#define POINTS (MAX_N / STEP)

long long operations = 0;

/* ---------- Merge ---------- */

void merge(int a[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        operations++;

        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];

    while (j <= right)
        temp[k++] = a[j++];

    for (i = left; i <= right; i++) {
        operations++;
        a[i] = temp[i];
    }
}

/* ---------- Standard Merge Sort ---------- */

void mergeSort(int a[], int temp[], int left, int right) {
    int mid;

    if (left >= right)
        return;

    mid = left + (right - left) / 2;

    mergeSort(a, temp, left, mid);
    mergeSort(a, temp, mid + 1, right);

    merge(a, temp, left, mid, right);
}

/* ---------- Three-Way Merge ---------- */

void mergeThree(
    int a[],
    int temp[],
    int left,
    int mid1,
    int mid2,
    int right
) {
    int i = left;
    int j = mid1 + 1;
    int k = mid2 + 1;
    int p = left;

    while (i <= mid1 || j <= mid2 || k <= right) {
        int smallest;
        int source;

        if (i <= mid1) {
            smallest = a[i];
            source = 1;
        } else if (j <= mid2) {
            smallest = a[j];
            source = 2;
        } else {
            smallest = a[k];
            source = 3;
        }

        if (j <= mid2) {
            operations++;

            if (a[j] < smallest) {
                smallest = a[j];
                source = 2;
            }
        }

        if (k <= right) {
            operations++;

            if (a[k] < smallest) {
                smallest = a[k];
                source = 3;
            }
        }

        temp[p++] = smallest;

        if (source == 1)
            i++;
        else if (source == 2)
            j++;
        else
            k++;
    }

    for (i = left; i <= right; i++) {
        operations++;
        a[i] = temp[i];
    }
}

/* ---------- Modified Three-Way Merge Sort ---------- */

void modifiedMergeSort(
    int a[],
    int temp[],
    int left,
    int right
) {
    int n;
    int mid1;
    int mid2;

    if (left >= right)
        return;

    n = right - left + 1;

    mid1 = left + n / 3 - 1;
    mid2 = left + (2 * n) / 3 - 1;

    if (mid1 < left)
        mid1 = left;

    if (mid2 <= mid1)
        mid2 = mid1 + 1;

    if (mid2 >= right)
        mid2 = right - 1;

    modifiedMergeSort(a, temp, left, mid1);
    modifiedMergeSort(a, temp, mid1 + 1, mid2);
    modifiedMergeSort(a, temp, mid2 + 1, right);

    mergeThree(a, temp, left, mid1, mid2, right);
}

/* ---------- Test Data ---------- */

void fillArray(int a[], int n) {
    int i;

    /*
     * Reverse order gives a non-trivial worst-case style input
     * for comparison counting.
     */
    for (i = 0; i < n; i++)
        a[i] = n - i;
}

/* ---------- Measurement ---------- */

long long measureStandard(int n) {
    int *a;
    int *temp;

    a = (int *)malloc(n * sizeof(int));
    temp = (int *)malloc(n * sizeof(int));

    fillArray(a, n);

    operations = 0;
    mergeSort(a, temp, 0, n - 1);

    free(a);
    free(temp);

    return operations;
}

long long measureModified(int n) {
    int *a;
    int *temp;

    a = (int *)malloc(n * sizeof(int));
    temp = (int *)malloc(n * sizeof(int));

    fillArray(a, n);

    operations = 0;
    modifiedMergeSort(a, temp, 0, n - 1);

    free(a);
    free(temp);

    return operations;
}

/* ---------- Raylib ---------- */

int main(void) {
    double standard[POINTS];
    double modified[POINTS];

    int i;
    double maxValue = 1.0;

    InitWindow(
        1250,
        800,
        "Merge Sort vs Modified Merge Sort - DAA Lab 02"
    );

    SetTargetFPS(60);

    /*
     * Generate experimental data once.
     */
    for (i = 0; i < POINTS; i++) {
        int n = (i + 1) * STEP;

        standard[i] = (double)measureStandard(n);
        modified[i] = (double)measureModified(n);

        if (standard[i] > maxValue)
            maxValue = standard[i];

        if (modified[i] > maxValue)
            maxValue = modified[i];
    }

    while (!WindowShouldClose()) {
        int gx = 100;
        int gy = 120;
        int gw = 1050;
        int gh = 500;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(
            "Merge Sort vs Modified Merge Sort",
            30,
            20,
            32,
            BLACK
        );

        DrawText(
            "Standard Merge Sort: T(n) = 2T(n/2) + O(n) = O(n log n)",
            30,
            60,
            20,
            DARKGRAY
        );

        DrawText(
            "Modified Merge Sort: T(n) = 3T(n/3) + O(n) = O(n log n)",
            30,
            88,
            20,
            DARKGRAY
        );

        /* Axes */

        DrawLine(
            gx,
            gy + gh,
            gx + gw,
            gy + gh,
            BLACK
        );

        DrawLine(
            gx,
            gy,
            gx,
            gy + gh,
            BLACK
        );

        /* X-axis */

        for (i = 0; i <= 10; i++) {
            int x = gx + i * gw / 10;

            DrawLine(
                x,
                gy + gh,
                x,
                gy + gh + 5,
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

        /* Y-axis */

        for (i = 1; i <= 5; i++) {
            int y = gy + gh - i * gh / 5;

            DrawLine(
                gx - 5,
                y,
                gx,
                y,
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

        /* Standard Merge Sort curve */

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
                    standard[i - 1] /
                    maxValue
                ) * gh;

            float y2 =
                gy + gh -
                (float)(
                    standard[i] /
                    maxValue
                ) * gh;

            DrawLineEx(
                (Vector2){x1, y1},
                (Vector2){x2, y2},
                3,
                BLUE
            );
        }

        /* Modified Merge Sort curve */

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
                    modified[i - 1] /
                    maxValue
                ) * gh;

            float y2 =
                gy + gh -
                (float)(
                    modified[i] /
                    maxValue
                ) * gh;

            DrawLineEx(
                (Vector2){x1, y1},
                (Vector2){x2, y2},
                3,
                RED
            );
        }

        /* Legend */

        DrawRectangle(
            120,
            660,
            25,
            5,
            BLUE
        );

        DrawText(
            "Standard Merge Sort",
            155,
            650,
            18,
            BLACK
        );

        DrawRectangle(
            500,
            660,
            25,
            5,
            RED
        );

        DrawText(
            "Modified Three-Way Merge Sort",
            535,
            650,
            18,
            BLACK
        );

        DrawText(
            "Input size (n)",
            560,
            735,
            18,
            DARKGRAY
        );

        DrawText(
            "Operation count",
            20,
            330,
            18,
            DARKGRAY
        );

        EndDrawing();
    }

    CloseWindow();

    return 0;
}