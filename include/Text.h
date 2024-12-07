#ifndef TEXT_H
#define TEXT_H

#include "raylib.h"
#include "EFont.h"
#include <string>
#include <iostream>
#include "AssetService.h"

class Text {
    private:
        std::string text;
        Font font;
        int fontSize;
        int spacing;
        Color color;
        Vector2 position;

    public:
        Text(std::string text, EFont font, int fontSize = 30, int spacing = 0, Color color = WHITE, Vector2 position = {100,100});
        ~Text();

        Vector2 getDimensions();

        void setPosition(Vector2 position) {
            this->position = position;
        }

        void setColor(Color color) {
            this->color = color;
        }

        std::string getText() {
            return this->text;
        }

        void setText(std::string text) {
            this->text = text;
        }

        void draw(); 
};

#endif