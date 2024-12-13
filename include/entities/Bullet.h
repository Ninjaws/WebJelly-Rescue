#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"
#include <cmath>
#include "entities/TextureWrapper.h"
#include "entities/Vector2i.h"
#include "services/MapService.h"
#include <iostream>

class Bullet
{
public:
    Bullet() {}
    Bullet(Vector2 pos, float direction)
    {
        this->position = pos;
        this->direction = direction;
        std::cout << direction << std::endl;
    }

    // ~Bullet() {}

    void logic()
    {
        move();
        hasCollided = false;
        envCollision();
        objCollision();
        //     // detectCollision();
    }

    void draw()
    {
        DrawCircle(position.x, position.y, size, color);
    }

    bool getHasCollided()
    {
        return this->hasCollided;
    }

protected:
    Color color = RED;

private:
    // TextureWrapper object;
    Vector2 position;
    float direction;
    float velocity = 15.0f;
    int size = 7;
    bool hasCollided = false;

    void move()
    {
        // float directionInRadians = this->direction * M_PI / 180.0f;
        position.x += velocity * cos(direction);
        position.y += velocity * sin(direction);
    }
    void envCollision()
    {
        if (position.y < 0 || position.y > GetScreenHeight())
        {
            hasCollided = true;
            return;
        }

        const int tileSize = MapService::getInstance().getMap().getTileSize();
        Vector2i tilePos = Vector2i((int)this->position.x / tileSize, (int)this->position.y / tileSize);
        if (MapService::getInstance().getMap().getColMap()[tilePos.y][tilePos.x] == 1)
        {
            hasCollided = true;
            return;
        }
    }
    virtual void objCollision() = 0;

    // void handleCollision() {

    // }
};

#endif