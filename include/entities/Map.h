#ifndef MAP_H
#define MAP_H

#include "raylib.h"
#include "entities/TextureWrapper.h"
#include "entities/Vector2i.h"
#include <vector>
#include <cmath>

/**
 * Holds the collision and texture maps for the game world
 */
class Map
{
public:
    Map();
    ~Map() {}

    void draw();

    /** Checks and returns which corners of the object have been collided with */
    // std::unordered_map<ECorner, bool> checkForCollision(TextureWrapper texture);

    int getTileSize() {
        return this->tileSize;
    }

    std::vector<std::vector<int>> getColMap() {
        return this->colMap;
    }

    void updateColmapTile(Vector2i tile, bool collision) {
        this->colMap[tile.y][tile.x] = collision ? 1 : 0;
    }

private:
    /** Holds the number for every single tile, which refers to a certain sprite in the tileset */
    std::vector<std::vector<Vector2>> map;
    /** Holds 1s (collision) and 0s (no collision) for every tile */
    std::vector<std::vector<int>> colMap;

    unsigned int tileSize = 32;

    Texture2D tileset;

    void loadMap();
    void loadColMap();
    void loadTileset();

    /**
     * Converts the corners of the object to the matching tiles, so that they can be checked for collision
     */
    // std::unordered_map<ECorner, Vector2> cornersToTilePos(std::unordered_map<ECorner, Vector2> corners);
};

#endif