#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "Screen.h"
#include "raylib.h"
#include "Text.h"
#include <string>
#include <vector>

class TitleScreen : public Screen {
private:
    Music bg;
    // std::vector<Text> text;

public:
    TitleScreen();
    ~TitleScreen();

    // void step() override;
    void logic() override;
    // void draw() override;
};

#endif