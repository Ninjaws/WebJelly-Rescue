#include "StateService.h"
#include "raylib.h"
#include "TitleScreen.h"
#include "MainScreen.h"
#include "TutorialScreen.h"
#include "GameScreen.h"
#include <optional>
#include "AudioService.h"

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
    InitAudioDevice();
    InitWindow(screenSize.x, screenSize.y, "Jelly Rescue");
    SetTargetFPS(60);

    setScreen(EScreen::TITLE);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(step, 0, 1);
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
    handleMusic();
    currentScreen->draw();
    currentScreen->logic();
}
