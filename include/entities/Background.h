#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "raylib.h"
#include "enums/EBackground.h"
#include <vector>
#include "entities/TextureWrapper.h"
#include "services/AssetService.h"
#include "services/StateService.h"

class Background {
    public:
    Background() {

    }
        Background(EBackground background){
            // Texture2D texture = AssetService::getInstance().getBackground(background);
            TextureWrapper wrapper = TextureWrapper(AssetService::getInstance().getBackground(background), StateService::getInstance().getScreenSize(), {0,0});
            wrapper.setSourceRect({0,0,wrapper.getSize().x, wrapper.getSize().y});
            textures.push_back(wrapper);
        }
        Background(std::vector<TextureWrapper> backgrounds){
            for(int i = 0; i < backgrounds.size(); i++) {
                this->textures.push_back(backgrounds[i]);
            }
        }
        ~Background(){}
        // Vector2 getPosition();
        // void updatePosition(Vector2 deltaPos);
        // void setPosition(Vector2 position);
        void draw(){
            for(int i = 0; i < textures.size(); i++) {
                TextureWrapper texture = textures[i];
                // Rectangle sourceRect = {0, 0, texture.getSize().x, texture.getSize().y};
                DrawTextureRec(texture.getTexture(), texture.getSourceRect(), texture.getPosition(),WHITE);
            }
        }
    private:
        std::vector<TextureWrapper> textures;
        // Vector2 position;
        // Vector2 size;
};


#endif