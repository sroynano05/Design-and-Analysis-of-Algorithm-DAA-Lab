
#include "raylib.h"
#include <math.h>

long double n_log2_n(long double n) { return (n > 0) ? n * log2l(n) : 0; }
long double t_sqrt(long double n) { return (n >= 0) ? 12 * sqrtl(n) : 0; }
long double inverse(long double n) { return (n > 0) ? (long double)1 / n : 0; }
long double n_pow_log2n(long double n) { return (n > 0) ? powl(n, log2l(n)) : 0; }
long double h_sqr_p_6_n(long double n) { return (n >= 0) ? n * (100 * n + 6) : 0; }
long double n_pow_51(long double n) { return (n >= 0) ? powl(n, 0.51) : 0; }
long double n_sqr_324(long double n) { return (n >= 0) ? (long double)(n * n - 324) : 0; }
long double n_05_50(long double n) { return (n >= 0) ? 50 * sqrtl(n) : 0; }
long double n_q_2(long double n) { return (n >= 0) ? n * n * n * 2 : 0; }
long double thre_pow_n(long double n) { return (n >= 0) ? powl(3, n) : 0; }
long double two_32_n(long double n) { return (n >= 0) ? (long double)n * 4294967296.0L : 0; }
long double log_2_n(long double n) { return (n > 0) ? log2l(n) : 0; }

typedef struct {
    long double (*func)(long double);
    Color color;
    const char *label;
} GraphFunction;

int main(void) {
    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Complexity Graphs");

    float scaleX = 10.0f;
    float scaleY = 0.1f;
    Vector2 origin = { 50.0f, (float)screenHeight - 50.0f };
    GraphFunction graphs[12] = {
        { n_log2_n, RED, "1. n_log2_n" },
        { t_sqrt, GREEN, "2. t_sqrt" },
        { inverse, BLUE, "3. inverse" },
        { n_pow_log2n, ORANGE, "4. n_pow_log2n" },
        { h_sqr_p_6_n, MAGENTA, "5. h_sqr_p_6_n" },
        { n_pow_51, PURPLE, "6. n_pow_51" },
        { n_sqr_324, LIME, "7. n_sqr_324" },
        { n_05_50, DARKGREEN, "8. n_05_50" },
        { n_q_2, SKYBLUE, "9. n_q_2" },
        { thre_pow_n, GOLD, "10. thre_pow_n" },
        { two_32_n, VIOLET, "11. two_32_n" },
        { log_2_n, PINK, "12. log_2_n" }
    };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) origin.x -= 5;
        if (IsKeyDown(KEY_LEFT)) origin.x += 5;
        if (IsKeyDown(KEY_UP)) origin.y += 5;
        if (IsKeyDown(KEY_DOWN)) origin.y -= 5;
        if (GetMouseWheelMove() > 0) { scaleX *= 1.1f; scaleY *= 1.1f; }
        if (GetMouseWheelMove() < 0) { scaleX *= 0.9f; scaleY *= 0.9f; }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        
        DrawLine(0, origin.y, screenWidth, origin.y, LIGHTGRAY);
        DrawLine(origin.x, 0, origin.x, screenHeight, LIGHTGRAY);

        
        for (int screenX = (int)origin.x; screenX < screenWidth; screenX++) {
            long double n = (long double)(screenX - origin.x) / scaleX;
            long double next_n = (long double)((screenX + 1) - origin.x) / scaleX;

            if (n < 0) continue;

            for (int i = 0; i < 12; i++) {
                long double y1 = graphs[i].func(n);
                long double y2 = graphs[i].func(next_n);

                float screenY1 = origin.y - (float)y1 * scaleY;
                float screenY2 = origin.y - (float)y2 * scaleY;

                if (screenY1 >= 0 && screenY1 <= screenHeight && screenY2 >= 0 && screenY2 <= screenHeight) {
                    DrawLine(screenX, screenY1, screenX + 1, screenY2, graphs[i].color);
                }
            }
        }

        DrawRectangle(10, 10, 240, 260, ColorAlpha(SKYBLUE, 0.2f));
        DrawRectangleLines(10, 10, 240, 260, BLUE);
        for (int i = 0; i < 12; i++) {
            DrawRectangle(20, 20 + (i * 20), 12, 12, graphs[i].color);
            DrawText(graphs[i].label, 40, 20 + (i * 20), 12, BLACK);
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
