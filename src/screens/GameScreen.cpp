#include "GameScreen.h"
#include "Map.h"
#include "StateService.h"

GameScreen::GameScreen()
{
    std::vector<EBackground> bgs;
    bgs.push_back(EBackground::GAME1);
    bgs.push_back(EBackground::GAME2);
    bgs.push_back(EBackground::GAME3);
    this->background = Background(bgs);
    this->map = Map();

    Vector2 screenSize = StateService::getInstance().getScreenSize();
    Camera2D camera = { 0 };
    camera.offset = (Vector2){ screenSize.x / 2.0f, screenSize.y / 2.0f };  // Set offset to center
    camera.target = (Vector2){ screenSize.x /2.0f, screenSize.y / 2.0f };  // Initially at the center of the world
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    this->camera = camera;
}

void GameScreen::logic()
{
    // this->background.value().updatePosition({-2.5f,0});
    this->camera.value().target.x += 1.0f;
}
