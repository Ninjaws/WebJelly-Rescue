#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "Screen.h"
#include "raylib.h"
#include "Text.h"

class TitleScreen : public Screen {
private:
    Music bg;
    std::vector<Text> text;

public:
    TitleScreen();

    void logic() override;
    void draw() override;
};

#endif