#include "MainScreen.h"
#include "AssetService.h"
#include "AudioService.h"
#include <iostream>
#include "StateService.h"

MainScreen::MainScreen()
{
    const int TOP_GAP = 100;
    const int BOTTOM_GAP = 50;
    const int AMNT_OF_BUTTONS = 4;
    const int TOTAL_SPACE = GetScreenHeight() - (TOP_GAP + BOTTOM_GAP);
    const int SPACE_PER_ITEM = TOTAL_SPACE / AMNT_OF_BUTTONS;

    for (int i = 0; i < AMNT_OF_BUTTONS; i++)
    {
        Text txt = Text("new game", EFont::GTEK, 30, 0, WHITE);
        text.push_back(txt);
    }

    text[0].setColor(RED);
    text[1].setText("load game");
    text[2].setText("tutorial");
    text[3].setText("quit");

    for (int i = 0; i < AMNT_OF_BUTTONS; i++)
    {
        text[i].setPosition({(float)(GetScreenWidth() - text[i].getDimensions().x) / 2.0f, (float)TOP_GAP + SPACE_PER_ITEM * i});
    }

    /** Will be ignored if already active (like when coming from the TitleScreen) */
    AudioService::getInstance().setMusic(EMusic::MAIN);
    AudioService::getInstance().playMusic();
}

MainScreen::~MainScreen()
{
}

void MainScreen::logic()
{
    // Vector2 mouseD = GetMouseDelta();
    // std::cout << mouseD.y <<std::endl;
    // if (mouseD.x != 0.0f && mouseD.y != 0.0f)
    // {
        // mouseLogic();
    // }

    keyboardLogic();
}

void MainScreen::mouseLogic()
{
    for (int i = 0; i < text.size(); i++)
    {
        /** No need to check the button that is already being hovered */
        if (hoveredButton == i)
            continue;

        Vector2 dim = text[i].getDimensions();
        Vector2 pos = text[i].getPosition();
        Rectangle rect = {pos.x, pos.y, dim.x, dim.y};

        Vector2 mousePos = GetMousePosition();
        // mousePos.x >= rect.x && mousePos.x <= (rect.x+rect.width) &&
        if (mousePos.x >= rect.x && mousePos.x <= (rect.x+rect.width) && mousePos.y >= rect.y && mousePos.y <= (rect.y + rect.height))
        {
            text[hoveredButton].setColor(WHITE);
            hoveredButton = i;
            text[hoveredButton].setColor(RED);
            break;
        }
    }
}

void MainScreen::keyboardLogic()
{
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_UP))
    {
        text[hoveredButton].setColor(WHITE);
        /** Move up or down depending on the pressed button. +4 is used so that -1 becomes 3 (the last button) */
        hoveredButton = ((hoveredButton - (IsKeyPressed(KEY_DOWN) ? -1 : 1)) + 4) % 4;
        text[hoveredButton].setColor(RED);
    }

    if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        std::cout << text[hoveredButton].getText() << std::endl;
        std::string selectedButton = text[hoveredButton].getText();


        if(selectedButton == "new game") {
        }
        else if(selectedButton == "load game") {
        }
        else if(selectedButton == "tutorial") {
            StateService::getInstance().setScreen(EScreen::TUTORIAL);
        }
        else if(selectedButton == "quit") {
            StateService::getInstance().setScreen(EScreen::CLOSE);
        }
    }
}