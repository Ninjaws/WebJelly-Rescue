#include "Screen.h"
#include "AudioService.h"
#include <optional>

void Screen::handleMusic()
{
    std::optional<Music> music = AudioService::getInstance().getMusic();
    if(music.has_value()) {
    UpdateMusicStream(music.value());
    }
}

void Screen::draw()
{
    handleMusic();
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