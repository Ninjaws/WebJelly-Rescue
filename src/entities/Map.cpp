#include "entities/Map.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "services/AssetService.h"
#include "entities/Map.h"

Map::Map()
{
    loadTileset();
    loadMap();
    loadColMap();
}

void Map::loadMap()
{
    std::vector<Vector2> tempMap;
    std::ifstream openfile(AssetService::getInstance().getMapUrl(EMap::TEXTURE));

    map.clear();

    if (openfile.is_open())
    {
        std::string tileLocation;
        openfile >> tileLocation;
        // tileTexture.loadFromFile(tileLocation);
        // tileSprites.setTexture(tileTexture);
        while (!openfile.eof())
        {
            std::string str, value;
            std::getline(openfile, str);
            std::stringstream stream(str);

            while (std::getline(stream, value, ' '))
            {
                if (value.length() > 0)
                {
                    std::string xx = value.substr(0, value.find(','));
                    std::string yy = value.substr(value.find(',') + 1);

                    int x = 0, y = 0, i, j;
                    // Look at all characters before the ','
                    for (i = 0; i < xx.length(); i++)
                    {
                        // if one of them is not a number, break
                        if (!isdigit(xx[i]))
                            break;
                    }
                    for (j = 0; j < yy.length(); j++)
                    {
                        if (!isdigit(yy[j]))
                            break;
                    }

                    // If all characters are numbers, convert string to int (the number that the sprite has in the sheet ( in this case, on the x axis)
                    if (i == xx.length())
                        x = atoi(xx.c_str());
                    else
                        x = -1;
                    // Otherwise, return -1 (aka no sprite)

                    if (j == yy.length())
                        y = atoi(yy.c_str());
                    else
                        y = -1;

                    // Hold both the x and y positions of the sprite
                    Vector2 vec2 = {(float)x, (float)y};
                    tempMap.push_back(vec2);
                }
            }

            if (tempMap.size() > 0)
            {
                map.push_back(tempMap);
                tempMap.clear();
            }
        }
    }
}

void Map::loadColMap()
{
    std::vector<int> tempColMap;
    std::ifstream openfile(AssetService::getInstance().getMapUrl(EMap::COLLISION));

    colMap.clear();

    if (openfile.is_open())
    {
        while (!openfile.eof())
        {
            std::string str;
            std::getline(openfile, str);
            std::stringstream stream(str);
            std::string value;
            while (std::getline(stream, value, ' '))
            {
                if (value.length() > 0)
                {
                    int tempValue = atoi(value.c_str());
                    tempColMap.push_back(tempValue);
                }
            }
            colMap.push_back(tempColMap);
            tempColMap.clear();
        }
    }
}

void Map::loadTileset()
{
    this->tileset = AssetService::getInstance().loadTexture("Textures/tileset.png");
}

std::unordered_map<ECorner, Vector2> Map::cornersToTilePos(std::unordered_map<ECorner, Vector2> corners)
{
    // std::cout << "Starting converting" << std::endl;
    std::unordered_map<ECorner, Vector2> cornersTilePos;
    for (const auto &pair : corners)
    {
        // std::cout << "Foreach pair" << std::endl;
        Vector2 original = corners[pair.first];
        cornersTilePos[pair.first] = {floorf(original.x / this->tileSize), floorf(original.y / this->tileSize)};
    }
    return cornersTilePos;
}

void Map::draw()
{
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j].x != -1 && map[i][j].y != -1)
            {
                // Rectangle source = {0,0,32,32};
                Rectangle sourceRect = {map[i][j].x * tileSize, map[i][j].y * tileSize, (float)tileSize, (float)tileSize};
                DrawTextureRec(tileset, sourceRect, {(float)j * tileSize, (float)i * tileSize}, WHITE);
                // tileSprites.setPosition(j * tileSize, i * tileSize);
                // tileSprites.setTextureRect(sf::IntRect(map[i][j].x * tileSize, map[i][j].y * tileSize, tileSize, tileSize));
                // GetWindow().draw(tileSprites);
            }
        }
    }
}

std::unordered_map<ECorner, bool> Map::checkForCollision(TextureWrapper texture)
{
    // std::cout << "Converting.." << std::endl;
    std::unordered_map<ECorner, Vector2> cornersTilePos = cornersToTilePos(texture.getCorners());
    // std::cout << "Done with converting" << std::endl;

    std::unordered_map<ECorner, bool> cornerCollisions;

     for (const auto &pair : cornersTilePos)
    {
        // std::cout << "foreach collision check" << std::endl;
        Vector2 pos = cornersTilePos[pair.first];
        // std::cout << pos.x << " " << pos.y << std::endl;
        if(colMap[pos.y][pos.x] == 1) {
            cornerCollisions[pair.first] = true;
        } else {
            cornerCollisions[pair.first] = false;
        }    
    }
    // std::cout << "Finished collision checks" << std::endl;

    return cornerCollisions;

    // for (int i = 0; i < tiles.size(); i++)
	// {
	// 	if (colMap[tiles[i].y][tiles[i].x] == 1)
	// 	{
	// 		timesCollision.push_back(i);
	// 	}
	// }

}
