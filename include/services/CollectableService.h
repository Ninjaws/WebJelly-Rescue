#ifndef COLLECTABLE_SERVICE_H
#define COLLECTABLE_SERVICE_H

#include "raylib.h"
#include "services/Service.h"
#include "services/MapService.h"
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

    void initCrates()
    {
        crates.clear();
        int tileSize = MapService::getInstance().getMap().getTileSize();
        for (int i = 0; i < amountOfCrates; i++)
        {
            crates.push_back(Crate());
        }
        crates[0].getObject().setPosition({38.0f * tileSize, 9.0f * tileSize});
        crates[1].getObject().setPosition({41.0f * tileSize, 5.0f * tileSize});
        crates[2].getObject().setPosition({68.0f * tileSize, 4.0f * tileSize});

        for (int i = 0; i < crates.size(); i++)
        {
            Vector2i crateTilePos = Vector2i(crates[i].getObject().getPosition().x / tileSize, crates[i].getObject().getPosition().y / tileSize);
            MapService::getInstance().getMap().updateColmapTile(crateTilePos, true);
        }
    }

    void initJellies()
    {
        jellies.clear();
    }

    void initAmmoPacks()
    {
        ammoPacks.clear();
        int tileSize = MapService::getInstance().getMap().getTileSize();
        for (int i = 0; i < amountOfAmmoPacks; i++)
        {
            ammoPacks.push_back(AmmoPack());
        }
        ammoPacks[0].getObject().setPosition({32.0f * tileSize, 9.0f * tileSize});
        ammoPacks[1].getObject().setPosition({48.0f * tileSize, 5.0f * tileSize});
        ammoPacks[2].getObject().setPosition({88.0f * tileSize, 9.0f * tileSize});
        ammoPacks[3].getObject().setPosition({105.0f * tileSize, 15.0f * tileSize});
    }

    void initHealthPacks()
    {
        healthPacks.clear();
        int tileSize = MapService::getInstance().getMap().getTileSize();
        for (int i = 0; i < amountOfHealthPacks; i++)
        {
            healthPacks.push_back(HealthPack());
        }
        healthPacks[0].getObject().setPosition({28.0f * tileSize, 10.0f * tileSize});
        healthPacks[1].getObject().setPosition({64.0f * tileSize, 6.0f * tileSize});
        healthPacks[2].getObject().setPosition({118.0f * tileSize, 11.0f * tileSize});
        healthPacks[3].getObject().setPosition({74.0f * tileSize, 8.0f * tileSize});
    }

    void initPowerups()
    {
        powerUps.clear();
        int tileSize = MapService::getInstance().getMap().getTileSize();
        for (int i = 0; i < amountOfPowerups; i++)
        {
            powerUps.push_back(Powerup());
        }
        powerUps[0].getObject().setPosition({41.0f * tileSize+8, 10.0f * tileSize-25});
    }

    void initFlag() {
        int tileSize = MapService::getInstance().getMap().getTileSize();
        this->flag = Flag({118.0f*tileSize-tileSize/2.0f, 3.0f * tileSize-8});
    }

    void crateLogic()
    {
        for (auto it = crates.begin(); it != crates.end();)
        {
            auto &crate = *it;
            /**
             * If the crate has been hit:
             * 1. Create a Jelly on the location of the crate
             * 2. Remove the collision tile from the collision map
             * 3. Remove the crate
             */
            if (crate.hasBeenHit())
            {
                Vector2 pos = crate.getObject().getPosition();

                jellies.push_back(Jelly(pos));

                Vector2i tilePos = Vector2i(pos.x / MapService::getInstance().getMap().getTileSize(), pos.y / MapService::getInstance().getMap().getTileSize());
                MapService::getInstance().getMap().updateColmapTile(tilePos, false);
                it = crates.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void jellyLogic()
    {
        for (int i = 0; i < jellies.size(); i++)
        {
            jellies[i].logic();
        }
    }

    void ammoPackLogic()
    {
        for (auto it = ammoPacks.begin(); it != ammoPacks.end();)
        {
            auto &ammoPack = *it;
            if (ammoPack.hasBeenPickedUp())
            {
                it = ammoPacks.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void healthPackLogic()
    {
        for (auto it = healthPacks.begin(); it != healthPacks.end();)
        {
            auto &healthPack = *it;
            if (healthPack.hasBeenPickedUp())
            {
                it = healthPacks.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void powerupLogic()
    {
        for (auto it = powerUps.begin(); it != powerUps.end();)
        {
            auto &powerUp = *it;
            if (powerUp.hasBeenPickedUp())
            {
                it = powerUps.erase(it);
            }
            else
            {
                powerUp.logic();
                ++it;
            }
        }
    }

    void drawCrates()
    {
        for (int i = 0; i < crates.size(); i++)
        {
            crates[i].draw();
        }
    }

    void drawJellies()
    {
        for (int i = 0; i < jellies.size(); i++)
        {
            jellies[i].draw();
        }
    }

    void drawAmmoPacks()
    {
        for (int i = 0; i < ammoPacks.size(); i++)
        {
            ammoPacks[i].draw();
        }
    }

    void drawHealthpacks()
    {
        for (int i = 0; i < healthPacks.size(); i++)
        {
            healthPacks[i].draw();
        }
    }

    void drawPowerups()
    {
        for (int i = 0; i < powerUps.size(); i++)
        {
            powerUps[i].draw();
        }
    }
};

#endif