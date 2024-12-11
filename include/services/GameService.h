#ifndef GAME_SERVICE_H
#define GAME_SERVICE_H

#include "Service.h"

class GameService : public Service<GameService> {
public:
    bool isPaused() {
        return this->paused;
    }

    bool isGameOver() {
        return this->gameOver;
    }

    void setPaused(bool paused) {
        this->paused = paused;
    }

    void setGameOver(bool gameOver) {
        this->gameOver = gameOver;
    }

private:
    bool paused = false;
    bool gameOver = false;
};


#endif