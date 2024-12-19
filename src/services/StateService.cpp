#include "raylib.h"
#include "services/StateService.h"
#include "services/AudioService.h"
#include "services/InputService.h"
#include "screens/TitleScreen.h"
#include "screens/MainScreen.h"
#include "screens/TutorialScreen.h"
#include "screens/GameScreen.h"
#include "screens/VictoryScreen.h"
#include <optional>

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
    case EScreen::TUTORIAL:
        currentScreen = std::make_unique<TutorialScreen>();
        break;
    case EScreen::GAME:
        currentScreen = std::make_unique<GameScreen>();
        break;
    case EScreen::VICTORY:
        currentScreen = std::make_unique<VictoryScreen>();
        break;
    case EScreen::CLOSE:
        gameRunning = false;
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
    // if(!instance)
    //     return;
    InitAudioDevice();
    // InitWindow(640,544, "Jelly Rescue");
    InitWindow(screenSize.x, screenSize.y, "Jelly Rescue");
    SetTargetFPS(45);
    #if not defined(PLATFORM_WEB)
    HideCursor();
    #endif

    setScreen(EScreen::TITLE);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(StateService::staticStep, 0, 1);
#else

    while (!WindowShouldClose() && gameRunning)
    {
        step();
    }
#endif

    CloseWindow();
    CloseAudioDevice();
}

void StateService::handleMusic()
{
    std::optional<Music> music = AudioService::getInstance().getMusic();
    if (music.has_value())
    {
        UpdateMusicStream(music.value());
    }
}

void StateService::step()
{
    InputService::getInstance().checkKeys();
    InputService::getInstance().checkMousePos();

    handleMusic();
    currentScreen->draw();
    currentScreen->logic();
}
