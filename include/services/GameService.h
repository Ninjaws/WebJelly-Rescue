#ifndef GAME_SERVICE_H
#define GAME_SERVICE_H

#include "services/Service.h"
#include "entities/Game.h"

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
    // void setGame(Game game) {
    //     this->game = game;
    // }

    // Game& getGame() {
    //     return this->game;
    // }

private:
    bool paused = false;
    bool gameOver = false;
    Camera2D camera;
};

#endif