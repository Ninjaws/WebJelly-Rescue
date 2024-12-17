#ifndef VICTORY_SCREEN_H
#define VICTORY_SCREEN_H

#include "raylib.h"
#include "screens/Screen.h"
#include "services/AssetService.h"
#include "entities/TextureWrapper.h"
#include "entities/Text.h"
#include "entities/Background.h"
#include <vector>

class VictoryScreen : public Screen
{

public:
    VictoryScreen();
    ~VictoryScreen() {
    }
    void logic() override;
    void draw() override;

private:
    std::vector<Text> text;
    std::vector<TextureWrapper> textures;
    std::vector<Text> buttons;
    int hoveredButton = 0;
    Background background;
};

#endif