#include "raylib.h"

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;
  InitWindow(screenWidth, screenHeight, "my-first-window");
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    for (int i = 150; i < 250; i++) {
      for (int j = 150; j < 250; j++) {
        DrawPixel(i, j, (Color){255, 128, 0, 255});
      }
    }
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
