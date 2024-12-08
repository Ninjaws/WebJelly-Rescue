#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

#include "Screen.h"

class MainScreen : public Screen {
private:
    int hoveredButton = 0;

    void mouseLogic();
    void keyboardLogic();
    void clickLogic();

public:
    MainScreen();

    void logic() override;
};

#endif