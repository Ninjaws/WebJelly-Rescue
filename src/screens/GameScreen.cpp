#include "screens/GameScreen.h"
#include "entities/Map.h"
#include "services/StateService.h"

GameScreen::GameScreen()
{
    // std::vector<EBackground> bgs;
    // bgs.push_back(EBackground::GAME1);
    // bgs.push_back(EBackground::GAME2);
    // bgs.push_back(EBackground::GAME3);
    // this->background = Background(bgs);
    // this->map = Map();
    
    this->game = Game();
    // this->camera = camera;
}

void GameScreen::logic()
{
    this->game.logic();
    // this->background.value().updatePosition({-2.5f,0});
    // this->camera.value().target.x += 1.0f;
}

void GameScreen::draw() {
    this->game.draw();
}
