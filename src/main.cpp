#include "raylib.h"
// #include "screens/Screen.h"
// #include "screens/TitleScreen.h"
#include "services/StateService.h"
// #include <iostream>

// #if defined(PLATFORM_WEB)
// #include <emscripten/emscripten.h>
// #endif

// void step();
// static void gameloop();

int main()
{
    StateService& stateService = StateService::getInstance();
    stateService.setScreenSize({640,544});
    stateService.startGame();
    // std::cout << "StateService instance: " << service << std::endl;

//     InitWindow(640, 544, "Jelly Rescue");
//     // SetTargetFPS(60);

//     // setScreen(EScreen::TITLE);

// #if defined(PLATFORM_WEB)
//     emscripten_set_main_loop(step, 0, 1);
// #else

//     while (!WindowShouldClose())
//     {
//         step();
//     }
// #endif

//     CloseWindow();

    return 0;
}

// static void gameloop()
// {
//     // InitAudioDevice();
//     InitWindow(640, 544, "Jelly Rescue");
//     // SetTargetFPS(60);

//     // setScreen(EScreen::TITLE);

// #if defined(PLATFORM_WEB)
//     emscripten_set_main_loop(step, 0, 1);
// #else

//     while (!WindowShouldClose())
//     {
//         step();
//     }
// #endif

//     CloseWindow();
//     // CloseAudioDevice();
// }

// void step()
// {
//     ClearBackground(BLACK);
// }