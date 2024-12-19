#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "services/AssetService.h"
#include "entities/TextureWrapper.h"
#include "entities/Vector2i.h"
#include <cmath>
#include <cstdint>

class Enemy
{
public:
    Enemy()
    {
        this->texture = TextureWrapper(AssetService::getInstance().getSprite(ESprite::ENEMY), {32, 32});
        this->gunRight = TextureWrapper(AssetService::getInstance().getSprite(ESprite::ENEMY_GUN_RIGHT), {97, 27});
        this->gunLeft = TextureWrapper(AssetService::getInstance().getSprite(ESprite::ENEMY_GUN_LEFT), {97, 27});
        prevFrame = GetTime();
        lastShot = GetTime();

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

    void logic();

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

    uint8_t getHealth()
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
    uint8_t health;
    uint8_t maxHealth = 5;
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
    float shotsPerSecond = 8.0f;
    double lastShot;
    bool playerSpotted = false;
    float aimSpeed = 2.0f; // How quickly the enemy can angle its gun to match the player (and to return to default)

    void walk();
    void checkForCollision();
    std::vector<Vector2i> getCorners();
    void animate();
    void drawHealthBar();
    void drawGun();
    void fall();
    void detectPlayer();
    void shoot();
};

#endif