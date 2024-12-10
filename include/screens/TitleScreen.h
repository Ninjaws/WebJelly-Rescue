#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "screens/Screen.h"
#include "raylib.h"
#include "entities/Text.h"

class TitleScreen : public Screen {
public:
    TitleScreen();

    void logic() override;
    void draw() override;

private:
    Music bg;
    std::vector<Text> text;
};

#endif