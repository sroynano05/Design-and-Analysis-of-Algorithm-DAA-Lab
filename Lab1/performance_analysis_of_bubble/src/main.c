#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define WIDTH 1000
#define HEIGHT 600
#define MAX_SIZE 2000
#define STEP 100
#define POINTS (MAX_SIZE / STEP)

long long std_bubble(int arr[], int n) {
    long long comps = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comps++;
            if (arr[j] > arr[j + 1]) {
                int t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
            }
        }
    }
    return comps;
}

long long opt_bubble(int arr[], int n) {
    long long comps = 0;
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            comps++;
            if (arr[j] > arr[j + 1]) {
                int t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
    return comps;
}

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Bubble Sort Performance");
    SetTargetFPS(60);

    int sizes[POINTS];
    long long std_comps[POINTS];
    long long opt_comps[POINTS];
    long long max_comps = 0;

    srand(time(NULL));

    
    for (int i = 0; i < POINTS; i++) {
        sizes[i] = (i + 1) * STEP;
        int n = sizes[i];
        
        int *arr1 = (int *)malloc(n * sizeof(int));
        int *arr2 = (int *)malloc(n * sizeof(int));
        
        for (int j = 0; j < n; j++) arr1[j] = rand() % 10000;
        for (int j = 0; j < n; j++) arr2[j] = arr1[j];
        
        std_comps[i] = std_bubble(arr1, n);
        opt_comps[i] = opt_bubble(arr2, n);
        
        if (std_comps[i] > max_comps) max_comps = std_comps[i];
        
        free(arr1);
        free(arr2);
    }

    int mx = 80, my = 60;
    int gw = WIDTH - mx * 2;
    int gh = HEIGHT - my * 2;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Comparisons: Standard (Red Line) vs Optimized (Blue Dots)", mx, 15, 20, DARKGRAY);
        DrawRectangleLines(mx, my, gw, gh, LIGHTGRAY);

        char max_str[32];
        sprintf(max_str, "%lld", max_comps);
        DrawText(max_str, mx - 70, my - 10, 15, DARKGRAY);
        DrawText("0", mx - 20, my + gh - 10, 15, DARKGRAY);
        
        char x_max_str[32];
        sprintf(x_max_str, "%d", MAX_SIZE);
        DrawText("0", mx, my + gh + 10, 15, DARKGRAY);
        DrawText(x_max_str, mx + gw - 30, my + gh + 10, 15, DARKGRAY);
        DrawText("Array Size (N)", WIDTH / 2 - 50, my + gh + 35, 20, DARKGRAY);

        for (int i = 1; i < POINTS; i++) {
            float x1 = mx + ((float)sizes[i-1] / MAX_SIZE) * gw;
            float x2 = mx + ((float)sizes[i] / MAX_SIZE) * gw;
            
            float y1_std = my + gh - ((float)std_comps[i-1] / max_comps) * gh;
            float y2_std = my + gh - ((float)std_comps[i] / max_comps) * gh;
            
            DrawLineEx((Vector2){x1, y1_std}, (Vector2){x2, y2_std}, 3.0f, RED);
        }

        for (int i = 0; i < POINTS; i++) {
            float x = mx + ((float)sizes[i] / MAX_SIZE) * gw;
            float y_opt = my + gh - ((float)opt_comps[i] / max_comps) * gh;
            
            DrawCircle(x, y_opt, 4.0f, BLUE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}