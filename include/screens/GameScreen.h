#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "screens/Screen.h"
#include "entities/Game.h"

class GameScreen: public Screen {

private:
    Game game;
protected:
public:
    GameScreen();
    void logic() override;
    void draw() override;
};

#endif