#ifndef TUTORIAL_SCREEN_H
#define TUTORIAL_SCREEN_H

#include "screens/Screen.h"
#include "entities/Background.h"
#include "entities/Text.h"

class TutorialScreen : public Screen
{
public:
    TutorialScreen();
    ~TutorialScreen() {}

    void logic() override;
    void draw() override;

private:
    std::vector<Text> text;
    Background background;
};

#endif