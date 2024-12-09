#ifndef SCREEN_H
#define SCREEN_H

class Screen
{
private:
protected:
    // std::optional<Map> map;
    // std::optional<Camera2D> camera;
    // std::optional<Map> map;
    // std::optional<Background> background;
    // std::vector<Text> text;

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
};

#endif
