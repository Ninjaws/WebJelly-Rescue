#include "entities/Bullet.h"
#include "services/MapService.h"

void Bullet::envCollision()
    {
        if (position.x < 0 || position.y < 0 || position.y > GetScreenHeight())
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