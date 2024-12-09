#ifndef TEXTURE_WRAPPER_H
#define TEXTURE_WRAPPER_H

#include "raylib.h"

class TextureWrapper {
    public:
        TextureWrapper(Texture2D texture, Vector2 size = {32,32}, Vector2 position = {0,0}, Rectangle sourceRect = {0,0,100,100}) {
            this->texture = texture;
            this->size = size;
            this->position = position;
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

        void setSourceRect(Rectangle rect) {
            this->sourceRect = rect;
        }

    private:
        Texture2D texture;
        Rectangle sourceRect;
        Vector2 size;
        Vector2 position;
};

#endif