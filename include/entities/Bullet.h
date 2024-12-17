#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"
#include "entities/TextureWrapper.h"
#include "entities/Vector2i.h"
#include <cmath>

class Bullet
{
public:
    Bullet() {}
    Bullet(Vector2 pos, float direction)
    {
        this->position = pos;
        this->direction = direction;
    }

    void logic()
    {
        move();
        hasCollided = false;
        objCollision();
        envCollision();
        //     // detectCollision();
    }

    void draw()
    {
        DrawCircleGradient(position.x, position.y, size, color, BLACK);
    }

    bool getHasCollided()
    {
        return this->hasCollided;
    }

protected:
    Color color = RED;
    Vector2 position;
    int size = 7;
    bool hasCollided = false;

private:
    float direction;
    float velocity = 15.0f;

    void move()
    {
        position.x += velocity * cos(direction);
        position.y += velocity * sin(direction);
    }
    void envCollision();
    virtual void objCollision() = 0;
};

#endif