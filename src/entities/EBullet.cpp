#include "entities/EBullet.h"
#include "services/PlayerService.h"

void EBullet::objCollision()
    {
        Player& player = PlayerService::getInstance().getPlayer();

         /** If the player is already falling of the map, dont allow bullets to hit it anymore */
            if(player.getHealth() == 0)
                return;

            if(this->position.x + this->size > player.getTexture().getPosition().x && this->position.x-this->size < player.getTexture().getPosition().x + player.getTexture().getSize().x && 
               this->position.y + this->size > player.getTexture().getPosition().y && this->position.y-this->size < player.getTexture().getPosition().y + player.getTexture().getSize().y) {
                player.takeDamage(this->damage);
                AssetService::getInstance().playSound(ESound::PLAYER_DAMAGE);
                this->hasCollided = true;
            }
    }