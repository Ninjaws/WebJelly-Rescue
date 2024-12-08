#include "TitleScreen.h"
#include "AssetService.h"
#include "StateService.h"
#include "EFont.h"
#include "AudioService.h"
#include <iostream>

TitleScreen::TitleScreen()
{
    Text textAbout = Text("Made by Ian Vink", EFont::SANSATION, 20,0, WHITE);
    textAbout.setPosition({
    (float)(GetScreenWidth()-textAbout.getDimensions().x)/1.2f, 
    (float)(GetScreenHeight()-textAbout.getDimensions().y)/6.0f
    });
    Text textCenter = Text("Jelly rescue", EFont::RECKONER_BOLD, 100, 0, {255,25,25,255});
    textCenter.setPosition({
    (float)(GetScreenWidth()-textCenter.getDimensions().x)/2.0f, 
    (float)(GetScreenHeight()-textCenter.getDimensions().y)/2.0f
    });
    Text testSub = Text("Press Enter", EFont::SANSATION, 30, 0, WHITE);
    testSub.setPosition({
    (float)(GetScreenWidth()-testSub.getDimensions().x)/2.0f, 
    (float)(GetScreenHeight()-testSub.getDimensions().y)/1.5f
    });

    text.push_back(textAbout);
    text.push_back(textCenter);
    text.push_back(testSub);


    AudioService::getInstance().setMusic(EMusic::MAIN);
    AudioService::getInstance().playMusic();

    // bg = LoadMusicStream("assets/Audio/Music/Crash_WarpRoomTheme.ogg");
    // bg.looping = true;
    // SetMasterVolume(1.0f);
    // SetMusicVolume(bg, 1.0f);
    // PlayMusicStream(bg);
}

TitleScreen::~TitleScreen()
{
    // UnloadMusicStream(bg);
}

void TitleScreen::logic()
{
    if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        StateService::getInstance().setScreen(EScreen::MAIN);
        // std::cout << "Next screen!" << std::endl;
    }
}