#ifndef TEXT_H
#define TEXT_H

#include "raylib.h"
#include "enums/EFont.h"
#include <string>
#include <iostream>
#include "services/AssetService.h"

class Text {
    public:
        Text(){}
        Text(std::string text, EFont font, int fontSize = 30, int spacing = 0, Color color = WHITE, Vector2 position = {100,100});
        ~Text(){}

        Vector2 getDimensions();

        void setPosition(Vector2 position) {
            this->position = position;
        }

        void setColor(Color color) {
            this->color = color;
        }

        void setText(std::string text) {
            this->text = text;
        }

        Vector2 getPosition() {
            return position;
        }

        std::string getText() {
            return this->text;
        }

        void draw(); 

    private:
        std::string text;
        Font font;
        int fontSize;
        int spacing;
        Color color;
        Vector2 position;
};

#endif