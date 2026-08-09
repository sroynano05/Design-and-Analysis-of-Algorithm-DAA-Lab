#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define WIDTH 1000
#define HEIGHT 600
#define TOSSES 1000000

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Coin Toss Simulation");
    SetTargetFPS(60);

    static float fair[TOSSES] = {0};
    static float biased[TOSSES] = {0};
    int f_heads = 0, b_heads = 0, step = 0;
    
    srand(time(NULL)); 
    float bias = 0.52f + ((float)rand() / RAND_MAX) * 0.03f; 

    int mx = 80, my = 60;
    int gw = WIDTH - mx * 2;
    int gh = HEIGHT - my * 2;

    while (!WindowShouldClose()) {
        for (int i = 0; i < 5000; i++) {
            if (step < TOSSES) {
                if ((float)rand() / RAND_MAX < 0.5f) f_heads++;
                if ((float)rand() / RAND_MAX < bias) b_heads++;
                
                fair[step] = (float)f_heads / (step + 1);
                biased[step] = (float)b_heads / (step + 1);
                step++;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Fair (Blue) vs Biased (Red)", mx, 15, 20, DARKGRAY);
        DrawRectangleLines(mx, my, gw, gh, LIGHTGRAY);

        int y50 = my + gh - (int)(0.5f * gh);
        DrawLine(mx, y50, mx + gw, y50, GRAY);
        DrawText("0.5", mx - 35, y50 - 10, 20, DARKGRAY);
        
        int stride = (step > 2000) ? step / 2000 : 1;
        
        for (int i = stride; i < step; i += stride) {
            int x1 = mx + (int)(((float)(i - stride) / TOSSES) * gw);
            int x2 = mx + (int)(((float)i / TOSSES) * gw);
            
            int y1f = my + gh - (int)(fair[i - stride] * gh);
            int y2f = my + gh - (int)(fair[i] * gh);
            DrawLine(x1, y1f, x2, y2f, BLUE);

            int y1b = my + gh - (int)(biased[i - stride] * gh);
            int y2b = my + gh - (int)(biased[i] * gh);
            DrawLine(x1, y1b, x2, y2b, RED);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
