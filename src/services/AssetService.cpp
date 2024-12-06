#include "AssetService.h"
#include <iostream>

void AssetService::setAssetDir(std::string newDir) {
    assetDir = newDir;
}

void AssetService::setAssets() {
    setAssetDir("assets/");

    fonts.push_back(loadFont("Fonts/Gtek.ttf"));
    fonts.push_back(loadFont("Fonts/Oxin.ttf"));
    fonts.push_back(loadFont("Fonts/Reckoner_Bold.ttf"));
    fonts.push_back(loadFont("Fonts/Reckoner.ttf"));
    fonts.push_back(loadFont("Fonts/Sansation.ttf"));

    music.push_back(loadMusic("Audio/Music/Crash_WarpRoomTheme.ogg", true));
}

Font AssetService::loadFont(std::string filename, int fontSize) {
    Font font = LoadFontEx((assetDir + filename).c_str(), fontSize,0,0);
    return font;
}

Font AssetService::loadFont(std::string filename) {
    Font font = LoadFont((assetDir + filename).c_str());
    return font;
}

Music AssetService::loadMusic(std::string filename, bool loops) {
    Music music = LoadMusicStream((assetDir + filename).c_str());
    music.looping = loops;
    return music;
}

Sound AssetService::loadSound(std::string filename)
{
    Sound sound = LoadSound((assetDir + filename).c_str());
    return sound;
}
