#ifndef MAP_SERVICE_H
#define MAP_SERVICE_H

#include "services/Service.h"
#include "entities/Map.h"
#include "entities/TextureWrapper.h"

/**
 * Allows all rigidbodies to check against the current Map
 */
class MapService : public Service<MapService>
{
public:
    void setMap(Map map)
    {
        this->map = Map();
    }

    Map& getMap() {
        return this->map;
    }

private:
    Map map;
};

#endif