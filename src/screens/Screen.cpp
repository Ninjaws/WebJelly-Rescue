#include "Screen.h"
#include "AudioService.h"
#include <optional>

void Screen::draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    if (text.size() > 0)
    {
        for (int t = 0; t < text.size(); t++)
        {
            text[t].draw();
        }
    }
    EndDrawing();
}