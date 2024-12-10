#ifndef SCREEN_H
#define SCREEN_H

class Screen
{
public:
    Screen(){}
    ~Screen() {}

    /**
     * Execute all logic for this frame
     */
    virtual void logic() = 0;
    /**
     * Draw frame to the screen
     */
    virtual void draw() = 0;

private:

};

#endif
