#ifndef PBULLET_H
#define PBULLET_H

#include "services/CollectableService.h"
#include "services/AssetService.h"
#include "services/EnemyService.h"
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
            if(this->position.x + this->size > crate.getObject().getPosition().x && this->position.x-this->size < crate.getObject().getPosition().x + crate.getObject().getSize().x && 
               this->position.y + this->size > crate.getObject().getPosition().y && this->position.y-this->size < crate.getObject().getPosition().y + crate.getObject().getSize().y) {
                crate.setHit(true);
                AssetService::getInstance().playSound(ESound::CRATE_BREAK);
                // AssetService::getInstance().playSound(ESound::JELLY_FREED);
                this->hasCollided = true;
            }
        }

        for (auto &enemy : EnemyService::getInstance().getEnemies())
        {
            /** If the enemy is already falling of the map, dont allow bullets to hit it anymore */
            if(enemy.getHealth() == 0)
                continue;

            if(this->position.x + this->size > enemy.getObject().getPosition().x && this->position.x-this->size < enemy.getObject().getPosition().x + enemy.getObject().getSize().x && 
               this->position.y + this->size > enemy.getObject().getPosition().y && this->position.y-this->size < enemy.getObject().getPosition().y + enemy.getObject().getSize().y) {
                enemy.takeDamage();
                if(enemy.getHealth() == 0) {
                    AssetService::getInstance().playSound(ESound::ENEMY_DEFEATED);
                }
                this->hasCollided = true;
            }
        }
    }
};

#endif