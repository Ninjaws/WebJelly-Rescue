#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "services/MapService.h"
#include "services/AssetService.h"
#include "entities/TextureWrapper.h"
#include <cmath>

class Enemy
{
public:
    Enemy()
    {
        this->texture = TextureWrapper(AssetService::getInstance().getSprite(ESprite::ENEMY), {32, 32});
        this->gunRight = TextureWrapper(AssetService::getInstance().getSprite(ESprite::ENEMY_GUN_RIGHT), {97, 27});
        this->gunLeft = TextureWrapper(AssetService::getInstance().getSprite(ESprite::ENEMY_GUN_LEFT), {97, 27});
        prevFrame = GetTime();

        /** Randomizes between 0 and 1 (+1 to get Left and Right in directions), so they dont all move in the same direction */
        int randDir = (int)((int)(GetTime() * 1000000) % 2);
        spriteAnimation = {0, randDir + 1};
        health = maxHealth;
    }
    Enemy(Vector2 startPos)
    {
        this->texture = TextureWrapper(AssetService::getInstance().getSprite(ESprite::ENEMY), {32, 32}, startPos);
        prevFrame = GetTime();

        int randDir = (int)((int)(GetTime() * 1000000) % 2);
        spriteAnimation = {0, randDir + 1};
        health = maxHealth;
    }

    void logic()
    {
        if (health == 0)
        {
            fall();
        }
        else
        {
            walk();
            checkForCollision();
            animate();
            // if (!hasCollided)
            // {
            // }
        }
        texture.move(velocity);
    }

    void draw()
    {
        drawGun();
        drawHealthBar();
        DrawTextureRec(this->texture.getTexture(), this->texture.getSourceRect(), this->texture.getPosition(), WHITE);
    }

    TextureWrapper &getObject()
    {
        return this->texture;
    }

    u_int8_t getHealth()
    {
        return this->health;
    }

    void takeDamage()
    {
        this->health = std::max(health - 1, 0);
    }

private:
    TextureWrapper texture;
    TextureWrapper gunLeft;
    TextureWrapper gunRight;
    u_int8_t health;
    u_int8_t maxHealth = 5;
    Vector2 velocity = {0, 0};
    float spottingRange = 300; // From how far away enemies can spot the player
    float gravity = 0.6f;
    float moveSpeed = 1.5f;
    float animationDelay = 0.2f; // In seconds
    double prevFrame;            // Time since the last frame
    bool hasCollided = false;
    Vector2i spriteAnimation; // Keeps track of (1) Sprite cycling and (2) Enemy direction
    enum Direction
    {
        Down,
        Left,
        Right,
        Up
    }; // Used in conjuction with spriteAnimation, makes sure sprite direction matches with enemy direction

    void walk()
    {
        if (spriteAnimation.y == Left)
        {
            velocity.x = -moveSpeed;
        }
        else
        {
            velocity.x = moveSpeed;
        }
    }

    void checkForCollision()
    {
        std::vector corners = getCorners();
        std::vector<std::vector<int>> colMap = MapService::getInstance().getMap().getColMap();
        hasCollided = false;

        if (colMap[corners[2].y][corners[2].x] == 0 || colMap[corners[3].y][corners[3].x] == 0) // No ground below enemy
        {
            hasCollided = true;
        }
        else if (colMap[corners[0].y][corners[0].x] == 1 || colMap[corners[1].y][corners[1].x] == 1)
        {
            hasCollided = true;
        }

        if (hasCollided)
        {
            if (spriteAnimation.y == Left)
                spriteAnimation.y = Right;
            else
                spriteAnimation.y = Left;

            velocity.x *= -1;
        }
    }

    std::vector<Vector2i> getCorners()
    {
        float bottom = texture.getPosition().y + texture.getSize().y + velocity.y;
        float left = texture.getPosition().x + velocity.x;
        float right = texture.getPosition().x + texture.getSize().x + velocity.x;
        float top = texture.getPosition().y + velocity.y;

        int tileSize = MapService::getInstance().getMap().getTileSize();
        // Vector2i leftTop(Vector2i((int)left / tileSize, (int)(top + 5) / tileSize));
        // Vector2i leftBottom(Vector2i((int)left / tileSize, (int)(bottom - 5) / tileSize));
        Vector2i leftCenter = Vector2i((int)left / tileSize, (int)(bottom - texture.getSize().y / 2.0) / tileSize);
        // Vector2i rightTop(Vector2i((int)right / tileSize, (int)(top + 5) / tileSize));
        // Vector2i rightBottom(Vector2i((int)right / tileSize, (int)(bottom - 5) / tileSize));
        Vector2i rightCenter = Vector2i((int)right / tileSize, (int)(bottom - texture.getSize().y / 2.0) / tileSize);

        Vector2i bottomLeft(Vector2i((int)(left + 5) / tileSize, (int)bottom / tileSize));   // +5 to separate bottom from side
        Vector2i bottomRight(Vector2i((int)(right - 5) / tileSize, (int)bottom / tileSize)); // -5 to separate bottom from side

        std::vector<Vector2i> corners;

        corners.push_back(leftCenter);
        corners.push_back(rightCenter);
        // corners.push_back(leftBottom);
        // corners.push_back(rightTop);
        // corners.push_back(rightBottom);

        corners.push_back(bottomLeft);
        corners.push_back(bottomRight);
        return corners;
    }

    void animate()
    {
        if (GetTime() - prevFrame > animationDelay || hasCollided)
        {
            spriteAnimation.x = std::fmod(spriteAnimation.x + 1, 3);

            Rectangle sourceRect = this->texture.getSourceRect();
            sourceRect.x = spriteAnimation.x * this->texture.getSize().x;
            sourceRect.y = spriteAnimation.y * this->texture.getSize().y;
            // sourceRect.x = std::fmod(sourceRect.x, 3 * this->texture.getSize().x);
            this->texture.setSourceRect(sourceRect);
            prevFrame = GetTime();
        }
    }

    void drawHealthBar()
    {
        float barLength = (this->texture.getSize().x / maxHealth) * health;
        DrawRectangle(this->texture.getPosition().x, this->texture.getPosition().y - 12.0f, barLength, 3, RED);
    }

    void drawGun()
    {
        if (this->spriteAnimation.y == Right)
        {
            DrawTexturePro(
                this->gunRight.getTexture(),
                {0, 0, this->gunRight.getSize().x, this->gunRight.getSize().y},
                {this->texture.getPosition().x + this->texture.getSize().x / 2.0f,
                 this->texture.getPosition().y + this->texture.getSize().y / 2.0f,
                 this->gunRight.getSize().x,
                 this->gunRight.getSize().y},
                {this->gunRight.getSize().x / 3.0f, this->gunRight.getSize().y / 2.0f},
                this->gunRight.getRotation(),
                WHITE);
        }
        else if (this->spriteAnimation.y == Left)
        {
            DrawTexturePro(
                this->gunLeft.getTexture(),
                {0, 0, this->gunLeft.getSize().x, this->gunLeft.getSize().y},
                {this->texture.getPosition().x + this->texture.getSize().x / 2.0f,
                 this->texture.getPosition().y + this->texture.getSize().y / 2.0f,
                 this->gunLeft.getSize().x,
                 this->gunLeft.getSize().y},
                {this->gunLeft.getSize().x - this->gunLeft.getSize().x / 3.0f, this->gunLeft.getSize().y / 2.0f},
                this->gunLeft.getRotation(),
                WHITE);
        }
    }

    void fall()
    {
        velocity.y += gravity;
    }
};

#endif