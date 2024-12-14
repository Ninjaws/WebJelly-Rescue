#ifndef PBULLET_H
#define PBULLET_H

#include "services/CollectableService.h"
#include "services/AssetService.h"
#include "entities/Bullet.h"
#include <iostream>

class PBullet : public Bullet
{
public:
    PBullet() {}
    PBullet(Vector2 pos, float angle) : Bullet(pos, angle)
    {
        this->color = YELLOW;
    }

private:
    void objCollision() override
    {
        /** Check for collisions with creates */
        for (auto &crate : CollectableService::getInstance().getCrates())
        {
            if(this->position.x + this->size > crate.getObject().getPosition().x && this->position.x - this->size < crate.getObject().getPosition().x && 
               this->position.y + this->size > crate.getObject().getPosition().y && this->position.y - this->size < crate.getObject().getPosition().y ) {
                crate.setHit(true);
                AssetService::getInstance().playSound(ESound::CRATE_BREAK);
                // AssetService::getInstance().playSound(ESound::JELLY_FREED);
                this->hasCollided = true;
            }
        }
    }
};

#endif