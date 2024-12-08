#include "TutorialScreen.h"

#include "StateService.h"
#include "EFont.h"
#include "EScreen.h"

TutorialScreen::TutorialScreen()
{
    Text textBack = Text("Press Enter to go back", EFont::SANSATION, 30, 0, RED);
    textBack.setPosition({(float)(GetScreenWidth() - textBack.getDimensions().x) / 1.3f,
                          (float)(GetScreenHeight() - textBack.getDimensions().y) / 1.15f});
    this->text.push_back(textBack);

    this->background = Background(EBackground::TUTORIAL);
}

void TutorialScreen::logic()
{
    if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        StateService::getInstance().setScreen(EScreen::MAIN);
    }
}
