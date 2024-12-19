#ifndef TEXTURE_WRAPPER_H
#define TEXTURE_WRAPPER_H

#include "raylib.h"
#include "enums/ECorner.h"

class TextureWrapper {
    public:
        TextureWrapper(){}
        TextureWrapper(Texture2D texture, Vector2 size = {32,32}, Vector2 position = {0,0}, Rectangle sourceRect = {0,0,32,32}) {
            this->texture = texture;
            this->size = size;
            this->position = position;
            this->sourceRect = sourceRect;
        }
        ~TextureWrapper() {
        }

        Texture2D getTexture() {
            return this->texture;
        }

        Rectangle getSourceRect(){
            return this->sourceRect;
        }

        Vector2 getSize() {
            return this->size;
        }

        Vector2 getPosition() {
            return this->position;
        }

        float getRotation() {
            return this->rotation;
        }

        void setSourceRect(Rectangle rect) {
            this->sourceRect = rect;
        }

        void setPosition(Vector2 position) {
            this->position = position;
        }

        void setRotation(float rot) {
            this->rotation = rot;
        }

        void move(Vector2 deltaPos) {
            this->position = {this->position.x + deltaPos.x, this->position.y + deltaPos.y};
        }

    private:
        Texture2D texture;
        Rectangle sourceRect;
        Vector2 size;
        Vector2 position;
        float rotation;
};

#endif