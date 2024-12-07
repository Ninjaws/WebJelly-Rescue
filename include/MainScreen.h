#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

#include "Screen.h"
#include "raylib.h"
#include <string>

class MainScreen : public Screen {
private:
    int hoveredButton = 0;

public:
    MainScreen();
    ~MainScreen();

    void logic() override;
};

#endif