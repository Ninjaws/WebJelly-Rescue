#ifndef CRATE_H
#define CRATE_H

#include "services/AssetService.h"
#include "entities/TextureWrapper.h"
#include "entities/PBullet.h"

class Crate {
public:
    Crate() {
        this->texture = TextureWrapper(AssetService::getInstance().getSprite(ESprite::CRATE),{32,32});
    }

    Crate(Vector2 pos) {
        this->texture = TextureWrapper(AssetService::getInstance().getSprite(ESprite::CRATE),{32,32}, pos);
    }

    void logic() {

    }

    bool hasBeenHit() {
        return this->hit;
    }

    void setHit(bool hit) {
        this->hit = hit;
    }

    void draw() {
        DrawTexture(this->texture.getTexture(), this->texture.getPosition().x, this->texture.getPosition().y, WHITE);
    }

    TextureWrapper& getObject() {
        return this->texture;
    }

private:
    TextureWrapper texture;
    bool hit;                   // Whether a PBullet has hit the crate
};

#endif