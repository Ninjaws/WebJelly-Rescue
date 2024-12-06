#include "StateService.h"
#include "raylib.h"
#include "TitleScreen.h"
#include "MainScreen.h"

StateService* StateService::instance = nullptr;

void StateService::setScreen(ScreenState state)
{
    switch (state)
    {
    case ScreenState::TITLE:
        currentScreen = std::make_unique<TitleScreen>();
        break;
    case ScreenState::MAIN:
        currentScreen = std::make_unique<MainScreen>();
        break;
    default:
        currentScreen = std::make_unique<TitleScreen>(); // Default case
    }
    // currentScreen = screen;
}

Screen* StateService::getScreen()
{
    return currentScreen.get();
}

void StateService::gameloop()
{
    InitAudioDevice();
    InitWindow(640, 544, "Jelly Rescue");
    SetTargetFPS(60);

    setScreen(ScreenState::TITLE);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(currentScreen->step, 0, 1);
#else

    while (!WindowShouldClose())
    {
        currentScreen->step();
        // UpdateDrawFrame();
    }
#endif

    CloseWindow();
    CloseAudioDevice();
}