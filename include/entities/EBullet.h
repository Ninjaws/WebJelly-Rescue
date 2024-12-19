#ifndef EBULLET_H
#define EBULLET_H

#include "services/AssetService.h"
#include "entities/Bullet.h"
#include <cstdint>

class EBullet : public Bullet
{
public:
    EBullet() {}
    EBullet(Vector2 pos, float angle) : Bullet(pos, angle)
    {
        this->color = RED;
    }

private:
    uint8_t damage = 1;
    void objCollision() override;
};

#endif