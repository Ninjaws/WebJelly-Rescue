#ifndef COLLECTABLE_SERVICE_H
#define COLLECTABLE_SERVICE_H

#include "raylib.h"
#include "services/Service.h"
#include "services/MapService.h"
#include "entities/Vector2i.h"
#include "entities/Crate.h"
#include "entities/PBullet.h"
#include <vector>

class CollectableService : public Service<CollectableService>
{
public:
    void initCollectables()
    {
        initCrates();
    }

    void collectableLogic()
    {
        crateLogic();
    }

    void drawCollectables()
    {
        drawCrates();
    }

    //  void checkCratesForCollision(PBullet bullet)
    // {
    //     for (auto it = crates.begin(); it != crates.end();)
    //     {
    //         auto &crate = *it;
    //         // if (*it % 2 == 0) {
    //         if (crate.bulletCollision(bullet))
    //         {
    //             Vector2 pos = crate.getObject().getPosition();
    //             Vector2i tilePos = Vector2i(pos.x / MapService::getInstance().getMap().getTileSize(), pos.y / MapService::getInstance().getMap().getTileSize());
    //             MapService::getInstance().getMap().updateColmapTile(tilePos, false);
    //             it = crates.erase(it); // erase returns the next iterator
    //         }
    //         else
    //         {
    //             ++it;
    //         }
    //     }
    // }

    std::vector<Crate>& getCrates() {
        return this->crates;
    }

private:
    void initCrates()
    {
        crates.clear();
        Vector2 location;
        int tileSize = MapService::getInstance().getMap().getTileSize();
        for (int i = 0; i < 3; i++)
        {
            crates.push_back(Crate());
            // crateLocation.push_back(location);
        }
        crates[0].getObject().setPosition({38.0f * tileSize, 9.0f * tileSize});
        crates[1].getObject().setPosition({41.0f * tileSize, 5.0f * tileSize});
        crates[2].getObject().setPosition({68.0f * tileSize, 4.0f * tileSize});

        for (int i = 0; i < crates.size(); i++)
        {
            Vector2i crateTilePos = Vector2i(crates[i].getObject().getPosition().x / tileSize, crates[i].getObject().getPosition().y / tileSize);
            MapService::getInstance().getMap().updateColmapTile(crateTilePos, true);
        }
        // crates[0].y = 9 * tileSize;

        // crateLocation[1].x = 41 * tileSize;
        // crateLocation[1].y = 5 * tileSize;

        // crateLocation[2].x = 68 * tileSize;
        // crateLocation[2].y = 4 * tileSize;
    }

    void initJellies()
    {
    }

    void crateLogic()
    {
        for (auto it = crates.begin(); it != crates.end();)
        {
            auto &crate = *it;
            /**
             * If the crate has been hit:
             * 1. Remove the collision tile from the collision map
             * 
             */
            if (crate.hasBeenHit())
            {
                Vector2 pos = crate.getObject().getPosition();
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

    // void destroyCrate(int index) {
    //     Vector2 pos = crates[index].getObject().getPosition();
    //     Vector2i tilePos = Vector2i(pos.x/MapService::getInstance().getMap().getTileSize(), pos.y/MapService::getInstance().getMap().getTileSize());
    //     MapService::getInstance().getMap().updateColmapTile(tilePos, false);
    //     crates.erase(crates.begin() + index);
    // }

    // void checkCratesForCollision(PBullet bullet)
    // {
    //     for (auto it = crates.begin(); it != crates.end();)
    //     {
    //         auto &crate = *it;
    //         // if (*it % 2 == 0) {
    //         if (crate.bulletCollision(bullet))
    //         {
    //             Vector2 pos = crate.getObject().getPosition();
    //             Vector2i tilePos = Vector2i(pos.x / MapService::getInstance().getMap().getTileSize(), pos.y / MapService::getInstance().getMap().getTileSize());
    //             MapService::getInstance().getMap().updateColmapTile(tilePos, false);
    //             it = crates.erase(it); // erase returns the next iterator
    //         }
    //         else
    //         {
    //             ++it;
    //         }
    //     }
    // }

    void jellyLogic()
    {
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
    }

    void drawHudJellies()
    {
    }

    void drawAmmoPacks()
    {
    }

    void drawHealthpacks()
    {
    }

    // sf::Text jelliesFreed;						// Holds the text that shows how many jellies are freed
    // sf::Font jelliesFreedFont;					// Holds the font used for the text of the display

    // sf::Sprite jelliesFreedSprite;				// Holds the sprite of the jelly in the top right corner

    // Vector2i jellyDisplayLocation;			// Holds the location where the amount of jellies freed are displayed
    std::vector<Crate> crates;
    // std::vector<sf::Sprite> crateSprite;		// Holds the sprites of the crates
    // std::vector<sf::Sprite> jellySprite;		// Holds the sprites of the jellies inside the crates
    // std::vector<Vector2> crateLocation;	// Holds the locations of the crates/jellies
    // std::vector<Vector2> velocity; // Makes sure the jellies jump when the crate is destroyed
    // std::vector<bool> collision;				// Keeps track of whether or not the player has collided with a crate
    // std::vector<bool> crateDestroyed;			// Keeps track of whether or not a crate has been destroyed

    // unsigned int totalAmntCrates;     // Holds the total amount of crates
    // unsigned int amntCratesDestroyed; // Holds the amount of crates that have been destroyed
};

#endif