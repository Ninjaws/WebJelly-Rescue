#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "screens/Screen.h"
#include "entities/Game.h"

class GameScreen: public Screen {

public:
    GameScreen();
    void logic() override;
    void draw() override;

private:
    Game game;
};

#endif