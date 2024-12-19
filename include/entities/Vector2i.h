#ifndef VECTOR2I_H
#define VECTOR2I_H

class Vector2i {
    public:
    Vector2i(){}
    Vector2i (int x, int y) {
        this->x = x;
        this->y = y;
    }
    int x;
    int y;
};

#endif