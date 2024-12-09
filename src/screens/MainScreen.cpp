#include "MainScreen.h"
#include "AudioService.h"
#include "StateService.h"
#include "raylib.h"

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
        buttons.push_back(txt);
    }
    buttons[0].setColor(RED);
    buttons[1].setText("load game");
    buttons[2].setText("tutorial");
    buttons[3].setText("quit");

    for (int i = 0; i < AMNT_OF_BUTTONS; i++)
    {
        buttons[i].setPosition({(float)(GetScreenWidth() - buttons[i].getDimensions().x) / 2.0f, (float)TOP_GAP + SPACE_PER_ITEM * i});
    }

    /** Will be ignored if already active (like when coming from the TitleScreen) */
    EMusic track = AudioService::getInstance().getCurrentTrack();
    if (track != EMusic::MAIN)
    {
        AudioService::getInstance().setMusic(EMusic::MAIN);
        AudioService::getInstance().playMusic();
    }
}

void MainScreen::logic()
{
    // Vector2 mouseD = GetMouseDelta();
    // std::cout << mouseD.y <<std::endl;
    // if (mouseD.x != 0.0f && mouseD.y != 0.0f)
    // {
    mouseLogic();
    // }

    keyboardLogic();

    clickLogic();
}


void MainScreen::mouseLogic()
{
    for (int i = 0; i < buttons.size(); i++)
    {
        /** No need to check the button that is already being hovered */
        if (hoveredButton == i)
            continue;

        /** Pixels around the text that also count towards that button, to make the hover feel better */
        int textPadding = 20;
        Vector2 dim = buttons[i].getDimensions();
        Vector2 pos = buttons[i].getPosition();
        Rectangle rect = {pos.x, pos.y, dim.x, dim.y};

        Vector2 mousePos = GetMousePosition();
        // mousePos.x >= rect.x && mousePos.x <= (rect.x+rect.width) &&
        if ((mousePos.x + textPadding) >= rect.x && mousePos.x <= (rect.x + rect.width + textPadding) && (mousePos.y + textPadding) >= rect.y && mousePos.y <= (rect.y + rect.height + textPadding))
        {
            buttons[hoveredButton].setColor(WHITE);
            hoveredButton = i;
            buttons[hoveredButton].setColor(RED);
            break;
        }
    }
}

void MainScreen::keyboardLogic()
{
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_UP))
    {
        buttons[hoveredButton].setColor(WHITE);
        /** Move up or down depending on the pressed button. +4 is used so that -1 becomes 3 (the last button) */
        hoveredButton = ((hoveredButton - (IsKeyPressed(KEY_DOWN) ? -1 : 1)) + 4) % 4;
        buttons[hoveredButton].setColor(RED);
    }
}

void MainScreen::clickLogic()
{
    if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        std::string selectedButton = buttons[hoveredButton].getText();

        if (selectedButton == "new game")
            StateService::getInstance().setScreen(EScreen::GAME);
        else if (selectedButton == "load game")
        {
        }
        else if (selectedButton == "tutorial")
            StateService::getInstance().setScreen(EScreen::TUTORIAL);
        else if (selectedButton == "quit")
            StateService::getInstance().setScreen(EScreen::CLOSE);
    }
}

void MainScreen::draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    if (buttons.size() > 0)
    {
        for (int i = 0; i < buttons.size(); i++)
        {
            buttons[i].draw();
        }
    }
    EndDrawing();
}