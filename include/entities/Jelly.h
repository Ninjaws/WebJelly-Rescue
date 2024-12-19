#ifndef JELLY_H
#define JELLY_H

#include "raylib.h"
#include "services/AssetService.h"
#include "entities/TextureWrapper.h"

class Jelly
{
public:
    Jelly(){
        this->texture = TextureWrapper(AssetService::getInstance().getSprite(ESprite::JELLY),{32,32});
        // AssetService::getInstance().playSound(ESound::JELLY_FREED);
    }
    Jelly(Vector2 startPos)
    {
        this->startPosition = startPos;
        this->texture = TextureWrapper(AssetService::getInstance().getSprite(ESprite::JELLY),{32,32},startPos);
        // AssetService::getInstance().playSound(ESound::JELLY_FREED);
    }

    void logic()
    {
        if (texture.getPosition().y >= startPosition.y)
        {
            velocity.y = -jumpSpeed;
        }
        else
        {
            velocity.y += gravity;
        }

        texture.move(velocity);
    }

    void draw()
    {
        DrawTexture(texture.getTexture(), texture.getPosition().x, texture.getPosition().y, WHITE);
    }

private:
    TextureWrapper texture;
    float jumpSpeed = 7.0f;
    float gravity = 0.6f;
    Vector2 velocity = {0, 0};
    Vector2 startPosition = {0,0};
};

#endif