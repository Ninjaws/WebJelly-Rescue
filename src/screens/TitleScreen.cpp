#include "screens/TitleScreen.h"
#include "services/AssetService.h"
#include "services/StateService.h"
#include "enums/EFont.h"
#include "services/AudioService.h"
#include "services/InputService.h"

TitleScreen::TitleScreen()
{
    Text textAbout = Text("Made by Ian Vink", EFont::SANSATION, 20, 0, WHITE);
    textAbout.setPosition({(float)(GetScreenWidth() - textAbout.getDimensions().x) / 1.2f,
                           (float)(GetScreenHeight() - textAbout.getDimensions().y) / 6.0f});
    Text textCenter = Text("Jelly rescue", EFont::RECKONER_BOLD, 100, 0, {255, 25, 25, 255});
    textCenter.setPosition({(float)(GetScreenWidth() - textCenter.getDimensions().x) / 2.0f,
                            (float)(GetScreenHeight() - textCenter.getDimensions().y) / 2.0f});
    Text testSub = Text("Press Enter", EFont::SANSATION, 30, 0, WHITE);
    testSub.setPosition({(float)(GetScreenWidth() - testSub.getDimensions().x) / 2.0f,
                         (float)(GetScreenHeight() - testSub.getDimensions().y) / 1.5f});

    text.push_back(textAbout);
    text.push_back(textCenter);
    text.push_back(testSub);

    EMusic track = AudioService::getInstance().getCurrentTrack();
    if (track != EMusic::MAIN)
    {
        AudioService::getInstance().setMusic(EMusic::MAIN);
        AudioService::getInstance().playMusic();
    }

    InputService::getInstance().setKeysToWatch({KEY_ENTER}, {MOUSE_BUTTON_LEFT});
}

void TitleScreen::logic()
{
    if (InputService::getInstance().isKeyPressed(KEY_ENTER) || InputService::getInstance().isMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        StateService::getInstance().setScreen(EScreen::MAIN);
    }
}

void TitleScreen::draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    if (text.size() > 0)
    {
        for (int t = 0; t < text.size(); t++)
        {
            text[t].draw();
        }
    }
    EndDrawing();
}