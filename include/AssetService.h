#ifndef ASSET_SERVICE_H
#define ASSET_SERVICE_H

#include <vector>
#include <string>
#include "raylib.h"

class AssetService
{
private:
    AssetService() {
        setAssets();
    };
    ~AssetService() = default;

    std::string assetDir;
    std::vector<Font> fonts;
    std::vector<Sound> sounds;
    std::vector<Music> music;
public:
    AssetService(const AssetService&) = delete;
    AssetService& operator=(const AssetService&) = delete;

    static AssetService& getInstance() {
        static AssetService instance;
        return instance;
    }

    std::vector<Font> getFonts() {
        return fonts;
    }

    std::vector<Sound> getSounds() {
        return sounds;
    }

    std::vector<Music> getMusic() {
        return music;
    }

    void setAssets();

    Font loadFont(std::string filename, int fontSize);
    Font loadFont(std::string filename);
    Music loadMusic(std::string filename, bool loops);
    Sound loadSound(std::string filename);

    void setAssetDir(std::string assetDir);

};

#endif