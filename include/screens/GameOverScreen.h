#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include "screens/Screen.h"
#include "raylib.h"
#include "services/AudioService.h"

class GameOverScreen : public Screen
{

public:
    GameOverScreen()
    {
        AudioService::getInstance().setMusic(EMusic::GAME_OVER);
        AudioService::getInstance().playMusic();
    }

    void logic() override
    {
    }

    void draw() override
    {
        BeginDrawing();
        // ClearBackground((Color){255,0,0,100});
         DrawRectangle(0, 0, 640, 544, (Color){255,0,0,65});
        EndDrawing();
    }

private:
};

#endif