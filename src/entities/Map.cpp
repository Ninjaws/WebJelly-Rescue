#include "Map.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "AssetService.h"

Map::Map()
{
    loadTileset();
    loadMap();
}

void Map::loadMap()
{
    std::vector<Vector2> tempMap;
    std::ifstream openfile("assets/Maps/map1.txt");

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

void Map::loadTileset()
{
    this->tileset = AssetService::getInstance().loadTexture("Textures/tileset.png");
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
                Rectangle sourceRect = {map[i][j].x * tileSize, map[i][j].y * tileSize, tileSize, tileSize};
                DrawTextureRec(tileset, sourceRect, {j * tileSize, i * tileSize}, WHITE);
                // tileSprites.setPosition(j * tileSize, i * tileSize);
                // tileSprites.setTextureRect(sf::IntRect(map[i][j].x * tileSize, map[i][j].y * tileSize, tileSize, tileSize));
                // GetWindow().draw(tileSprites);
            }
        }
    }
}
