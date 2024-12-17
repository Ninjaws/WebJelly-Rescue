#ifndef PLAYER_SERVICE_H
#define PLAYER_SERVICE_H

#include "raylib.h"
#include "services/Service.h"
#include "entities/Player.h"
#include <memory>

class PlayerService : public Service<PlayerService>
{
public:
    void initPlayer()
    {
        this->player = std::make_unique<Player>();
        this->player->setPosition({200, 350});
    }

    Player& getPlayer() {
        return *this->player;
    }

protected:
private:
    std::unique_ptr<Player> player;
};

#endif