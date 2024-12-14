#ifndef GAME_SERVICE_H
#define GAME_SERVICE_H

#include "services/Service.h"
#include "entities/Game.h"
#include "entities/PBullet.h"
#include <vector>
#include <list>

class GameService : public Service<GameService>
{
public:
    bool isPaused()
    {
        return this->paused;
    }

    bool isGameOver()
    {
        return this->gameOver;
    }

    void setPaused(bool paused)
    {
        this->paused = paused;
    }

    void setGameOver(bool gameOver)
    {
        this->gameOver = gameOver;
    }
    void setCamera(Camera2D camera)
    {
        this->camera = camera;
    }

    Camera2D &getCamera()
    {
        return this->camera;
    }

    /**
     * Returns the position of the mouse in world coordinates
     */
    Vector2 getMouseWorldPos()
    {
        Vector2 mouseWorldPos = {GetMousePosition().x + camera.target.x - camera.offset.x, GetMousePosition().y};
        return mouseWorldPos;
    }

    Vector2 toWorldPos(Vector2i pixelPos) {
      Vector2 worldPos = {(float)pixelPos.x + camera.target.x - camera.offset.x, (float)pixelPos.y};
        return worldPos;  
    }
    // void setGame(Game game) {
    //     this->game = game;
    // }

    // Game& getGame() {
    //     return this->game;
    // }

    void addPlayerBullet(PBullet bullet)
    {
        this->playerBullets.push_back(bullet);
    }

    // std::list<PBullet>& getPlayerBullets() {
    //     return this->playerBullets;
    // }

    // void removeCollidedBullets()
    // {
    //     for (auto it = playerBullets.begin(); it != playerBullets.end(); /* no increment here */)
    //     {
    //         if (it->getHasCollided())
    //         {
    //             it = playerBullets.erase(it); // Remove element and get the next valid iterator
    //         }
    //         else
    //         {
    //             ++it; // Only increment if no removal happens
    //         }
    //     }
    // }

    void bulletLogic()
    {
        for (auto it = this->playerBullets.begin(); it != this->playerBullets.end();)
        {
            it->logic();
            if (it->getHasCollided())
                it = this->playerBullets.erase(it);
            else
                ++it;
        }
    }

    void drawBullets()
    {
       for (auto it = this->playerBullets.begin(); it != this->playerBullets.end();)
        {
            it->draw();
            ++it;
        }
    }

    void resetGame()
    {
        paused = false;
        gameOver = false;
        // playerBullets.clear();
    }

private:
    bool paused = false;
    bool gameOver = false;
    Camera2D camera;

    std::list<PBullet> playerBullets;
};

#endif