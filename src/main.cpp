#include "raylib.h"

int main() {
    // Initialize window
    InitWindow(800, 600, "Raylib + Emscripten Test");

    // Main game loop
    while (!WindowShouldClose()) {
        // Update (empty for now)

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, Raylib on WebAssembly!", 190, 200, 20, DARKGRAY);
        EndDrawing();
    }

    // Close window
    CloseWindow();

    return 0;
}