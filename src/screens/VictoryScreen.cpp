#include "screens/VictoryScreen.h"
#include "services/InputService.h"
#include "services/AudioService.h"
#include "services/CollectableService.h"
#include <string>
#include <sstream>

VictoryScreen::VictoryScreen()
{
    AudioService::getInstance().stopMusic();
    AssetService::getInstance().playSound(ESound::VICTORY);

    Text victory = Text("victory", EFont::GTEK, 50, 0, {255, 0, 0, 255});
    victory.setPosition({(float)(GetScreenWidth() - victory.getDimensions().x) / 2.0f,
                         (float)(GetScreenHeight() - victory.getDimensions().y) / 2.5f});

    int amntOfJelliesRescued = CollectableService::getInstance().getAmountOfJelliesFreed();
    int maxAmntOfJellies = CollectableService::getInstance().getMaxAmountOfJellies();
    std::string rescuedString;
    if (amntOfJelliesRescued == maxAmntOfJellies)
    {
        rescuedString = "You have rescued all of the jellies!";
    }
    else
    {
        std::stringstream stream;
        stream << "You have rescued ";
        stream << amntOfJelliesRescued;
        stream << " of the ";
        stream << maxAmntOfJellies;
        stream << " jellies";
        rescuedString = stream.str();
    }

    Text rescued = Text(rescuedString, EFont::SANSATION, 30, 0, WHITE);
    rescued.setPosition({(float)(GetScreenWidth() - rescued.getDimensions().x) / 2.0f,
                         (float)(GetScreenHeight() - rescued.getDimensions().y) / 1.5f});

    this->text.push_back(victory);
    this->text.push_back(rescued);


    const int TOP_POS = GetScreenHeight()/1.2;
    const int X_GAP = 70;
    const int AMNT_OF_BUTTONS = 2;
    const int TOTAL_SPACE = GetScreenWidth() - X_GAP * 2;
    const int SPACE_PER_ITEM = TOTAL_SPACE / AMNT_OF_BUTTONS;

    for (int i = 0; i < AMNT_OF_BUTTONS; i++)
    {
        Text txt = Text("Play Again", EFont::SANSATION, 30, 0, WHITE);
        buttons.push_back(txt);
    }
    buttons[0].setColor(RED);
    buttons[1].setText("Return to Main Menu");
    buttons[0].setPosition({(float)X_GAP, (float)TOP_POS});
    buttons[1].setPosition({(float)GetScreenWidth() - X_GAP - buttons[1].getDimensions().x, (float)TOP_POS});

    const int x_gap = 50;
    const int available_space = GetScreenWidth() - x_gap * 2;
    const int space_per_jelly = available_space / maxAmntOfJellies;
    for (int i = 0; i < amntOfJelliesRescued; i++)
    {
        TextureWrapper wrapper = TextureWrapper(AssetService::getInstance().getSprite(ESprite::JELLY), {32, 32});
        wrapper.setPosition({(float)x_gap + space_per_jelly * i + space_per_jelly / 2.0f - wrapper.getSize().x / 2.0f, GetScreenHeight() / 2.0f});
        textures.push_back(wrapper);
    }

    this->background = Background(EBackground::VICTORY);

    InputService::getInstance().setKeysToWatch({KEY_ENTER, KEY_A, KEY_D}, {});
}

void VictoryScreen::logic()
{
        if (InputService::getInstance().isKeyPressed(KEY_D) || InputService::getInstance().isKeyPressed(KEY_A))
        {
            buttons[hoveredButton].setColor(WHITE);
            hoveredButton = ((hoveredButton - (InputService::getInstance().isKeyPressed(KEY_D) ? -1 : 1)) + buttons.size()) % buttons.size();
            buttons[hoveredButton].setColor(RED);
        }

        if (InputService::getInstance().isKeyPressed(KEY_ENTER))
        {
            std::string selectedButton = buttons[hoveredButton].getText();

            if (selectedButton == "Play Again")
            {
                StateService::getInstance().setScreen(EScreen::GAME);
            }
            else if (selectedButton == "Return to Main Menu")
            {
                StateService::getInstance().setScreen(EScreen::MAIN);
            }
        }
}

void VictoryScreen::draw()
{
    BeginDrawing();
    this->background.draw();

    for (int t = 0; t < text.size(); t++)
    {
        text[t].draw();
    }

    for (int t = 0; t < buttons.size(); t++)
    {
        buttons[t].draw();
    }

    for (int t = 0; t < textures.size(); t++)
    {
        DrawTexture(textures[t].getTexture(), textures[t].getPosition().x, textures[t].getPosition().y, WHITE);
    }

    EndDrawing();
}
