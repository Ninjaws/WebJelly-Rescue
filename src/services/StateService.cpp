#include "services/StateService.h"
#include "raylib.h"
#include "screens/TitleScreen.h"
#include "screens/MainScreen.h"
#include "screens/TutorialScreen.h"
#include "screens/GameScreen.h"
#include <optional>
#include "services/AudioService.h"
#include "services/InputService.h"

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
    // if(!instance)
    //     return;
    InitAudioDevice();
    // InitWindow(640,544, "Jelly Rescue");
    InitWindow(screenSize.x, screenSize.y, "Jelly Rescue");
    SetTargetFPS(60);

    // #if defined(PLATFORM_WEB)
    //  emscripten_set_keypress_callback(EMSCRIPTEN_EVENT_TARGET_CANVAS, nullptr, 1, staticStep);
    //  #endif

    // #if defined(PLATFORM_WEB)
    //     emscripten_set_focusin_callback(EMSCRIPTEN_EVENT_TARGET_CANVAS, nullptr, 1, [](const EmscriptenFocusEvent* event) {
    //     std::cout << "Canvas Focused!" << std::endl;
    // });
    // #endif

    setScreen(EScreen::TITLE);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(StateService::staticStep, 0, 1);
#else

    // while (!WindowShouldClose() && instance->gameRunning)
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

    handleMusic();
    currentScreen->draw();
    currentScreen->logic();
}
