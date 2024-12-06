#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

#include "Screen.h"
#include "raylib.h"
#include <string>

class MainScreen : public Screen {
private:
    Music bg;
    Font font1;
    Font font2;
    std::string assetDir;
    Vector2 dimTitle;
    Vector2 dimSub;
    Vector2 dimHead;

    void logic() override;
    void draw() override;
public:
    MainScreen();
    ~MainScreen();

    void step() override;
};

#endif