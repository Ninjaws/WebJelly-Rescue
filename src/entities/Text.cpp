#include "Text.h"

Text::Text(std::string text, EFont font, int fontSize, int spacing, Color color, Vector2 position)
{
    Font fnt = AssetService::getInstance().getFont(font, fontSize);

    this->text = text;
    this->font = fnt;
    this->fontSize = fontSize;
    this->spacing = spacing;
    this->color = color;
    this->position = position;
}

Text::~Text()
{
    // Causes double free for some reason
    // UnloadFont(this->font);
}

Vector2 Text::getDimensions()
{
    return MeasureTextEx(font, text.c_str(), (float)fontSize, (float)spacing);
}

void Text::draw()
{
    DrawTextEx(font, text.c_str(), position, fontSize, spacing, color);
}
