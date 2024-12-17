#ifndef GAME_SERVICE_H
#define GAME_SERVICE_H

#include "raylib.h"
#include "services/Service.h"
#include "services/AudioService.h"
#include "services/InputService.h"
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
        if (this->paused)
            AudioService::getInstance().pauseMusic();
    }

    void setGameOver(bool gameOver)
    {
        this->gameOver = gameOver;
        if (this->gameOver)
        {
            AudioService::getInstance().setMusic(EMusic::GAME_OVER);
            AudioService::getInstance().playMusic();
        }
    }

    void setCamera(Camera2D camera)
    {
        this->camera = camera;
    }

    Camera2D &getCamera()
    {
        return this->camera;
    }

    Vector2 getMouseWorldPos()
    {
        Vector2 mouseWorldPos = {InputService::getInstance().getMousePos().x + camera.target.x - camera.offset.x, 
                                 InputService::getInstance().getMousePos().y};
        return mouseWorldPos;
    }

    Vector2 toWorldPos(Vector2i pixelPos)
    {
        Vector2 worldPos = {(float)pixelPos.x + camera.target.x - camera.offset.x, (float)pixelPos.y};
        return worldPos;
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
};

#endif