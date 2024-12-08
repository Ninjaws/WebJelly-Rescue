#include "Screen.h"
#include "AudioService.h"
#include <optional>

Screen::Screen()
{
}

void Screen::draw()
{
    BeginDrawing();

    if (camera.has_value())
        BeginMode2D(this->camera.value());

    if (!background.has_value())
        ClearBackground(BLACK);
    else
        this->background.value().draw();

    if (map.has_value())
        this->map.value().draw();

    if (text.size() > 0)
    {
        for (int t = 0; t < text.size(); t++)
        {
            text[t].draw();
        }
    }
    if (camera.has_value())
        EndMode2D();

    EndDrawing();
}