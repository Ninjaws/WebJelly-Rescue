#include "services/EnemyService.h"
#include "services/MapService.h"

void EnemyService::initEnemies()
{
    this->enemies.clear();
    const int AMNT_OF_ENEMIES = 8;
    int tileSize = MapService::getInstance().getMap().getTileSize();
    for (int i = 0; i < AMNT_OF_ENEMIES; i++)
    {
        enemies.push_back(Enemy());
    }
    this->enemies[0].getObject().setPosition({31.0f * tileSize, 15.0f * tileSize});
    this->enemies[1].getObject().setPosition({51.0f * tileSize, 10.0f * tileSize});
    this->enemies[2].getObject().setPosition({56.0f * tileSize, 5.0f * tileSize});
    this->enemies[3].getObject().setPosition({78.0f * tileSize, 10.0f * tileSize});
    this->enemies[4].getObject().setPosition({81.0f * tileSize, 15.0f * tileSize});
    this->enemies[5].getObject().setPosition({88.0f * tileSize, 4.0f * tileSize});
    this->enemies[6].getObject().setPosition({98.0f * tileSize, 11.0f * tileSize});
    this->enemies[7].getObject().setPosition({103.0f * tileSize, 15.0f * tileSize});
}

void EnemyService::enemyLogic()
{
    for (auto it = enemies.begin(); it != enemies.end();)
    {
        auto &enemy = *it;
        if (enemy.getObject().getPosition().y < 0)
        {
            it = enemies.erase(it);
        }
        else
        {
            enemy.logic();
            ++it;
        }
    }
}

void EnemyService::drawEnemies()
{
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].draw();
    }
}

std::vector<Enemy> &EnemyService::getEnemies()
{
    return this->enemies;
}