#ifndef POWERUP_H
#define POWERUP_H

#include "raylib.h"
#include "services/AssetService.h"
#include "entities/TextureWrapper.h"
#include <cstdint>

class Powerup {
    public:
        Powerup() {
            this->object = TextureWrapper(AssetService::getInstance().getSprite(ESprite::POWERUP),{50,55});
        }
        void logic(){
            animate();
        }

        void draw() {
            DrawTextureRec(object.getTexture(), object.getSourceRect(), object.getPosition(), WHITE);
        }

        float getExtraJumpPower() {
            return this->extraJumpPower;
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
        float extraJumpPower = 2.0f;     // Jump power gained by grabbing the powerup
        bool pickedUp = false;           // When the player has picked up the pack  
        float animationDelay = 0.08f;    // How long to wait in between animation frames (in seconds)
        double lastFrame;                // Time since the last frame
        uint8_t currentFrame = 0;       // Current frame of the animation
        uint8_t amountOfFrames = 8;     // Total amount of animation frames

        void animate() {
            if(GetTime() - lastFrame > animationDelay) {
                currentFrame ++;
                currentFrame %= amountOfFrames;

                object.setSourceRect({(float)currentFrame * 81 + 16, 10,object.getSize().x, object.getSize().y});
                lastFrame = GetTime();
            }
        }
};


#endif