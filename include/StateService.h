#ifndef STATE_SERVICE_H
#define STATE_SERVICE_H

#include "Screen.h"
#include <iostream>
#include <memory>
#include "EScreen.h"
#include "Service.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

class StateService : public Service<StateService>
{
private:
    std::unique_ptr<Screen> currentScreen;

    bool gameRunning = true;

    /**
     * One step of the gameloop
     */
    void step();

    void handleMusic();
    
public:

    void setScreen(EScreen screen);
    Screen *getScreen();
    /**
     * Start the game loop
     */
    void startGame();
};

#endif