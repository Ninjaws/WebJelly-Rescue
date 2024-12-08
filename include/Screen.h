#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include "Text.h"
#include "raylib.h"
#include <optional>
#include "Background.h"
#include "Map.h"

class Screen {
    private:

    protected:
        // std::optional<Map> map;
        std::optional<Camera2D> camera;
        std::optional<Map> map;
        std::optional<Background> background;
        std::vector<Text> text;

    public:
        Screen();
        ~Screen(){}

        /**
         * Execute all logic for this frame
         */
        virtual void logic() = 0;
        /**
         * Draw frame to the screen
         */
        void draw();

};

#endif
