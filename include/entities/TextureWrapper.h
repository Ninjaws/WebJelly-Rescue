#ifndef TEXTURE_WRAPPER_H
#define TEXTURE_WRAPPER_H

#include "raylib.h"
#include "enums/ECorner.h"
#include <unordered_map>

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

        /** Returns the 4 corners of the texture */
        // std::unordered_map<ECorner, Vector2> getCorners() {
		// std::unordered_map<ECorner, Vector2> corners;
        // float top = this->position.y;
        // float right = this->position.x+this->size.x;
        // float bottom = this->position.y + this->size.y;
        // float left = this->position.x;
        // float margin = 8; // Space to the corner
		// corners[ECorner::TOP_LEFT] = {left+margin, top};
		// corners[ECorner::TOP_RIGHT] = {right-margin, top};
        // corners[ECorner::RIGHT_TOP] = {right, top+margin};
        // corners[ECorner::RIGHT_BOTTOM] = {right, bottom-margin};
		// corners[ECorner::BOTTOM_RIGHT] = {right-margin, bottom};
		// corners[ECorner::BOTTOM_LEFT] = {left+margin, bottom};
        // corners[ECorner::LEFT_BOTTOM] = {left, bottom-margin};
        // corners[ECorner::LEFT_TOP] = {left, top+margin};

		// return corners;
        // }

    private:
        Texture2D texture;
        Rectangle sourceRect;
        Vector2 size;
        Vector2 position;
        float rotation;
};

#endif