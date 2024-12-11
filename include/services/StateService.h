#ifndef STATE_SERVICE_H
#define STATE_SERVICE_H

#include <iostream>
#include <memory>
#include "services/Service.h"
#include "screens/Screen.h"
#include "enums/EScreen.h"
#include "raylib.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

/**
 * Handles switching between screens
 */
class StateService : public Service<StateService>
{
public:
    Vector2 getScreenSize()
    {
        return screenSize;
    }
    void setScreenSize(Vector2 screenSize)
    {
        this->screenSize = screenSize;
    }
    void setScreen(EScreen screen);
    Screen *getScreen();
    /**
     * Start the game loop
     */
    void startGame();
    static void staticStep()
    {
        if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            std::cout << "Input!" << std::endl;
        }
        // Access the singleton instance and call step
        getInstance().step();
    }

private:
    std::unique_ptr<Screen> currentScreen;
    bool gameRunning = true;
    Vector2 screenSize;

    /**
     * One step of the gameloop
     */
    void step();
    void handleMusic();
};

#endif