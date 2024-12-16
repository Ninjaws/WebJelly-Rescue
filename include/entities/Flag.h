#ifndef FLAG_H
#define FLAG_H

#include "raylib.h"
#include "services/AssetService.h"
#include "services/StateService.h"
#include "entities/TextureWrapper.h"

class Flag
{
public:
    Flag()
    {
        this->texture = TextureWrapper(AssetService::getInstance().getSprite(ESprite::FLAG), {40, 40});
    }
    Flag(Vector2 startPos)
    {
        this->texture = TextureWrapper(AssetService::getInstance().getSprite(ESprite::FLAG), {40, 40}, startPos);
    }

    void logic()
    {
        if (touched)
        {
            StateService::getInstance().setScreen(EScreen::VICTORY);
        }
    }

    void draw()
    {
        DrawTextureEx(texture.getTexture(), texture.getPosition(), 0.0f, texture.getSize().x/texture.getTexture().width, WHITE);
    }

    TextureWrapper &getObject()
    {
        return this->texture;
    }

    void setTouched(bool touched) {
        this->touched = touched;
    }

private:
    TextureWrapper texture;
    bool touched = false; // Whether the player has touched the flag
};

#endif