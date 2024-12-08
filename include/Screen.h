#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include "Text.h"

class Screen {
    private:

    protected:
        std::vector<Text> text;

    public:
        Screen(){}
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
