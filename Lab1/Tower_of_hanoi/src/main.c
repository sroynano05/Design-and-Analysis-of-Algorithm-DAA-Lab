#include "raylib.h"
#include <math.h>
#include <stdio.h>

long long powerOfTwoMinusOne(int n) {
    return (1LL << n) - 1;
}

int main(void) {
    const int screenWidth = 900;
    const int screenHeight = 650;
    
    InitWindow(screenWidth, screenHeight, "Tower of Hanoi - Moves Graph (Raylib)");
    SetTargetFPS(60);

   
    const float originX = 100.0f;
    const float originY = 550.0f;
    const float graphWidth = 750.0f;
    const float graphHeight = 450.0f;

    int maxN = 10; 

    while (!WindowShouldClose()) {
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

       
        DrawText("Tower of Hanoi: Disks vs. Number of Moves ($2^n - 1$)", 180, 25, 20, DARKGRAY);

      
        long long maxMoves = powerOfTwoMinusOne(maxN);
        int ySteps = 5;
        for (int i = 0; i <= ySteps; i++) {
            float yVal = (float)i / ySteps * maxMoves;
            float posY = originY - (i / (float)ySteps) * graphHeight;

            
            DrawLine(originX, posY, originX + graphWidth, posY, LIGHTGRAY);

            
            char label[32];
            sprintf(label, "%lld", (long long)yVal);
            DrawText(label, originX - 75, posY - 10, 10, DARKGRAY);
        }

        DrawLine(originX, originY, originX + graphWidth, originY, BLACK); // X-axis
        DrawLine(originX, originY - graphHeight, originX, originY, BLACK); // Y-axis

      
        Vector2 points[10];
        for (int i = 0; i < maxN; i++) {
            int n = i + 1;
            long long moves = powerOfTwoMinusOne(n);

            float xCoord = originX + ((float)(i) / (maxN - 1)) * graphWidth;
            float yCoord = originY - ((float)moves / maxMoves) * graphHeight;

            points[i] = (Vector2){ xCoord, yCoord };

            char nLabel[16];
            sprintf(nLabel, "%d", n);
            DrawText(nLabel, xCoord - 5, originY + 10, 12, DARKGRAY);
        }

        for (int i = 0; i < maxN - 1; i++) {
            DrawLineV(points[i], points[i+1], BLUE);
        }

        
        for (int i = 0; i < maxN; i++) {
            DrawCircleV(points[i], 5, RED);
            
            
            char valStr[16];
            sprintf(valStr, "%lld", powerOfTwoMinusOne(i + 1));
            DrawText(valStr, points[i].x - 12, points[i].y - 22, 10, DARKGRAY);
        }

      
        DrawText("Number of Disks (n)", originX + (graphWidth / 2) - 60, originY + 35, 12, BLACK);
        DrawText("Moves", originX - 45, originY - (graphHeight / 2) - 10, 12, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}