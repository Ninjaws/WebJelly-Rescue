#ifndef SCREEN_H
#define SCREEN_H

class Screen {
    private:

        /**
         * All the logic that concerns the screen currently visible to the player
         */
        virtual void logic();
        /**
         * Draws everything for the current screen
         */
        virtual void draw();
    public:
        Screen();
        ~Screen();


        /**
         * One step of the game loop
         */
        virtual void step();

};

#endif
