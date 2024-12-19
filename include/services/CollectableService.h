#ifndef COLLECTABLE_SERVICE_H
#define COLLECTABLE_SERVICE_H

#include "raylib.h"
#include "services/Service.h"
#include "entities/Vector2i.h"
#include "entities/Crate.h"
#include "entities/Jelly.h"
#include "entities/AmmoPack.h"
#include "entities/HealthPack.h"
#include "entities/Powerup.h"
#include "entities/Flag.h"
#include <vector>

/**
 * Service that manages the collectables (jellies), consumables (Ammo, health, powerups), and the finish flag
 */
class CollectableService : public Service<CollectableService>
{
public:
    void initCollectables()
    {
        initCrates();
        initJellies();
        initAmmoPacks();
        initHealthPacks();
        initPowerups();
        initFlag();
    }

    void collectableLogic()
    {
        crateLogic();
        jellyLogic();
        ammoPackLogic();
        healthPackLogic();
        powerupLogic();
        flag.logic();
    }

    void drawCollectables()
    {
        drawCrates();
        drawJellies();
        drawAmmoPacks();
        drawHealthpacks();
        drawPowerups();
        flag.draw();
    }

    std::vector<Crate> &getCrates()
    {
        return this->crates;
    }

    std::vector<AmmoPack> &getAmmoPacks()
    {
        return this->ammoPacks;
    }

    std::vector<HealthPack> &getHealthPacks()
    {
        return this->healthPacks;
    }

    std::vector<Powerup> &getPowerups() {
        return this->powerUps;
    }

    Flag& getFlag() {
        return this->flag;
    }

    int getMaxAmountOfJellies()
    {
        return this->amountOfCrates;
    }

    int getAmountOfJelliesFreed()
    {
        return this->jellies.size();
    }

private:
    int amountOfCrates = 3;
    int amountOfAmmoPacks = 4;
    int amountOfHealthPacks = 4;
    int amountOfPowerups = 1;
    std::vector<Crate> crates;
    std::vector<AmmoPack> ammoPacks;
    std::vector<HealthPack> healthPacks;
    std::vector<Jelly> jellies;
    std::vector<Powerup> powerUps;
    Flag flag;

    void initCrates();
    void initJellies();
    void initAmmoPacks();
    void initHealthPacks();
    void initPowerups();
    void initFlag();
    void crateLogic();
    void jellyLogic();
    void ammoPackLogic();
    void healthPackLogic();
    void powerupLogic();
    void drawCrates();
    void drawJellies();
    void drawAmmoPacks();
    void drawHealthpacks();
    void drawPowerups();
};

#endif