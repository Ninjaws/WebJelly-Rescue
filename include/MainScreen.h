#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

#include "Screen.h"
#include <vector>
#include "Text.h"

class MainScreen : public Screen {
private:
    int hoveredButton = 0;
    std::vector<Text> buttons;

    void mouseLogic();
    void keyboardLogic();
    void clickLogic();

public:
    MainScreen();

    void logic() override;
    void draw() override;
};

#endif