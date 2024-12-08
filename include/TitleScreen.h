#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "Screen.h"
#include "raylib.h"

class TitleScreen : public Screen {
private:
    Music bg;

public:
    TitleScreen();

    void logic() override;
};

#endif