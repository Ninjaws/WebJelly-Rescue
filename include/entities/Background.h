#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "raylib.h"
#include "enums/EBackground.h"
#include <vector>
#include "entities/TextureWrapper.h"
#include "services/AssetService.h"
#include "services/StateService.h"

class Background
{
public:
    Background()
    {
    }
    Background(EBackground background)
    {
        TextureWrapper wrapper = TextureWrapper(AssetService::getInstance().getBackground(background), StateService::getInstance().getScreenSize(), {0, 0});
        wrapper.setSourceRect({0, 0, wrapper.getSize().x, wrapper.getSize().y});
        textures.push_back(wrapper);
    }
    Background(std::vector<TextureWrapper> backgrounds)
    {
        for (int i = 0; i < backgrounds.size(); i++)
        {
            this->textures.push_back(backgrounds[i]);
        }
    }
    ~Background() {}
    void draw()
    {
        for (int i = 0; i < textures.size(); i++)
        {
            TextureWrapper texture = textures[i];
            DrawTextureRec(texture.getTexture(), texture.getSourceRect(), texture.getPosition(), WHITE);
        }
    }

    Vector2 getBackgroundSize()
    {
        TextureWrapper lastbg = this->textures[this->textures.size() - 1];
        return {lastbg.getPosition().x + lastbg.getSize().x, lastbg.getPosition().y + lastbg.getSize().y};
    }

private:
    std::vector<TextureWrapper> textures;
};

#endif