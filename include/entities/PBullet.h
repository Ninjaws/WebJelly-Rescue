#ifndef PBULLET_H
#define PBULLET_H

#include "entities/Bullet.h"
#include <iostream>

class PBullet : public Bullet {
public:

    PBullet() {}
    PBullet(Vector2 pos, float angle) : Bullet(pos, angle) {
        this->color = YELLOW;
    }


private:
    void objCollision() override {

        }

};

#endif