#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "raylib.h"
#include "EBackground.h"
#include <vector>

class Background {
    private:
        Vector2 position;
        std::vector<Texture2D> textures;
    protected:
    public:
        Background(EBackground background);
        Background(std::vector<EBackground> backgrounds);
        ~Background(){}
        Vector2 getPosition();
        void updatePosition(Vector2 deltaPos);
        void setPosition(Vector2 position);
        void draw();
};


#endif