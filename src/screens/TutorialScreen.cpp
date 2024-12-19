#include "screens/TutorialScreen.h"
#include "enums/EScreen.h"
#include "enums/EFont.h"
#include "services/StateService.h"
#include "services/InputService.h"

TutorialScreen::TutorialScreen() {
    Text textBack = Text("Press Enter to go back", EFont::SANSATION, 30, 0, RED);
    textBack.setPosition({(float)(GetScreenWidth() - textBack.getDimensions().x) / 1.3f,
                          (float)(GetScreenHeight() - textBack.getDimensions().y) / 1.15f});
    this->text.push_back(textBack);

    this->background = Background(EBackground::TUTORIAL);

    InputService::getInstance().setKeysToWatch({KEY_ENTER},{});
}

void TutorialScreen::logic()
{
    if ( InputService::getInstance().isKeyPressed(KEY_ENTER))
    {
        StateService::getInstance().setScreen(EScreen::MAIN);
    }
}

void TutorialScreen::draw()
{
    BeginDrawing();
    this->background.draw();

    if (text.size() > 0)
    {
        for (int t = 0; t < text.size(); t++)
        {
            text[t].draw();
        }
    }
    EndDrawing();
}
