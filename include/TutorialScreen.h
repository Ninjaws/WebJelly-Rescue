#ifndef TUTORIAL_SCREEN_H
#define TUTORIAL_SCREEN_H

#include "Screen.h"
#include "Background.h"
#include "Text.h"

class TutorialScreen : public Screen
{
private:
    std::vector<Text> text;
    Background background;

protected:
public:
    TutorialScreen();
    ~TutorialScreen() {}

    void logic() override;
    void draw() override;
};

#endif