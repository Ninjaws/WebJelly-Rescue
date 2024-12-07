#include "StateService.h"
#include "raylib.h"
#include "TitleScreen.h"
#include "MainScreen.h"

void StateService::setScreen(EScreen state)
{
    switch (state)
    {
    case EScreen::TITLE:
        currentScreen = std::make_unique<TitleScreen>();
        break;
    case EScreen::MAIN:
        currentScreen = std::make_unique<MainScreen>();
        break;
    default:
        currentScreen = std::make_unique<TitleScreen>();
    }
}

Screen *StateService::getScreen()
{
    return currentScreen.get();
}

void StateService::startGame()
{
    InitAudioDevice();
    InitWindow(640, 544, "Jelly Rescue");
    SetTargetFPS(60);

    setScreen(EScreen::TITLE);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(step, 0, 1);
#else

    while (!WindowShouldClose())
    {
        step();
    }
#endif

    CloseWindow();
    CloseAudioDevice();
}

void StateService::step()
{
    currentScreen->draw();
    currentScreen->logic();
}