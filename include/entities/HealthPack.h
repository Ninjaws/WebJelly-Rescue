#ifndef HEALTH_PACK_H
#define HEALTH_PACK_H

#include "raylib.h"
#include "services/AssetService.h"
#include "entities/TextureWrapper.h"

class HealthPack {
    public:
        HealthPack() {
            this->object = TextureWrapper(AssetService::getInstance().getSprite(ESprite::HEALTHPACK),{32,32});
        }
        void logic(){
        }

        void draw() {
            DrawTexture(object.getTexture(), object.getPosition().x, object.getPosition().y, WHITE);
        }

        int getHealAmount() {
            return this->healAmount;
        }

        void setPickedUp(bool pickedUp) {
            this->pickedUp = pickedUp;
        }

        bool hasBeenPickedUp() {
            return this->pickedUp;
        }

        TextureWrapper& getObject() {
            return this->object;
        }

    private:
        TextureWrapper object;
        unsigned int healAmount = 2;    // Amount of health replenished by the pack
        bool pickedUp;                  // When the player has picked up the pack   
};


#endif