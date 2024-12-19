#ifndef ENEMY_SERVICE_H
#define ENEMY_SERVICE_H

#include "raylib.h"
#include "services/Service.h"
#include "entities/Enemy.h"
#include <optional>

class EnemyService : public Service<EnemyService>
{
public:
    void initEnemies();
    void enemyLogic();
    void drawEnemies();
    std::vector<Enemy> &getEnemies();

protected:
private:
    std::vector<Enemy> enemies;
};

#endif