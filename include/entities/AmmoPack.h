#ifndef AMMO_PACK_H
#define AMMO_PACK_H

#include "raylib.h"
#include "services/AssetService.h"
#include "entities/TextureWrapper.h"

class AmmoPack {
    public:
        AmmoPack() {
            this->object = TextureWrapper(AssetService::getInstance().getSprite(ESprite::AMMOPACK),{32,32});
        }
        void logic(){
        }

        void draw() {
            DrawTexture(object.getTexture(), object.getPosition().x, object.getPosition().y, WHITE);
        }

        int getAmmoAmount() {
            return this->ammoAmount;
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
        unsigned int ammoAmount = 10;   // Amount of ammo replenished by the pack
        bool pickedUp;                  // When the player has picked up the pack   
};


#endif