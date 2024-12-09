#ifndef STATE_SERVICE_H
#define STATE_SERVICE_H

#include "Screen.h"
#include <iostream>
#include <memory>
#include "EScreen.h"
#include "Service.h"
#include "raylib.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

/**
 * Handles switching between screens
 */
class StateService : public Service<StateService>
{
private:
    std::unique_ptr<Screen> currentScreen;

    bool gameRunning = true;

    Vector2 screenSize;

    /**
     * One step of the gameloop
     */
    void step();

    void handleMusic();
    
public:
    Vector2 getScreenSize(){
        return screenSize;
    }
    void setScreenSize(Vector2 screenSize) {
        this->screenSize = screenSize;
    }
    void setScreen(EScreen screen);
    Screen *getScreen();
    /**
     * Start the game loop
     */
    void startGame();
};

#endif