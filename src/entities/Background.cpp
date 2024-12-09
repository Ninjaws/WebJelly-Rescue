#include "Background.h"

#include "AssetService.h"

// Background::Background(EBackground background)
// {
//     this->textures.push_back(AssetService::getInstance().getBackground(background));
//     this->position = {0,0};
// }

// Background::Background(std::vector<EBackground> backgrounds)
// {
//     for(int i = 0; i < backgrounds.size(); i++) {
//         this->textures.push_back(AssetService::getInstance().getBackground(backgrounds[i]));
//         this->position = {0,0};
//     }
// }

// Vector2 Background::getPosition()
// {
//     return  this->position;
// }

// void Background::updatePosition(Vector2 deltaPos)
// {
//     this->position = {this->position.x+deltaPos.x, this->position.y+deltaPos.y};
// }

// void Background::setPosition(Vector2 position)
// {
//     this->position = position;
// }

// void Background::draw()
// {
//     for(int i = 0; i < textures.size(); i++) {
//         DrawTexture(textures[i], position.x+ (i != 0 ? i*textures[i-1].width : 0), position.y, WHITE);
//     }
// }
