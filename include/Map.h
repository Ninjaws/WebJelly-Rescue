#ifndef MAP_H
#define MAP_H

#include <vector>
#include "raylib.h"

/**
 * Holds the collision and texture maps for the game world
 */
class Map
{
public:
    Map();
    ~Map() {}

    void draw();

private:
    /** Holds the number for every single tile, which refers to a certain sprite in the tileset */
    std::vector<std::vector<Vector2>> map;
    /** Holds 1s (collision) and 0s (no collision) for every tile   */
    std::vector<std::vector<int>> colMap;

    float tileSize = 32;

    Texture2D tileset;

    void loadMap();
    void loadColMap(){}
    void loadTileset();
};

#endif