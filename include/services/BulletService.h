#ifndef BULLET_SERVICE_H
#define BULLET_SERVICE_H

#include "raylib.h"
#include "services/Service.h"
#include "services/AssetService.h"
#include "entities/PBullet.h"
#include "entities/EBullet.h"
#include <optional>
#include <memory>

class BulletService : public Service<BulletService>
{
public:
    void initBullets()
    {
        this->bullets.clear();
    }

    void bulletLogic()
    {
        for (auto it = this->bullets.begin(); it != this->bullets.end();)
        {
            (*it)->logic();
            if ((*it)->getHasCollided())
                it = this->bullets.erase(it);
            else
                ++it;
        }
    }

    void drawBullets()
    {
        for (auto it = this->bullets.begin(); it != this->bullets.end();)
        {
            (*it)->draw();
            ++it;
        }
    }

    void addPlayerBullet(Vector2 position, float direction)
    {
        this->bullets.push_back(std::make_unique<PBullet>(position, direction));
    }

    void addEnemyBullet(Vector2 position, float direction)
    {
        this->bullets.push_back(std::make_unique<EBullet>(position, direction));
    }

protected:
private:
    std::vector<std::unique_ptr<Bullet>> bullets;
};

#endif