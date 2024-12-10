#include "services/AssetService.h"
#include <iostream>
AssetService::AssetService()
{
    setAssetDir("assets/");
    setAssets();
}


void AssetService::setAssets()
{
    fonts[EFont::GTEK] = "Fonts/Gtek.ttf";
    fonts[EFont::OXIN] = "Fonts/Oxin.ttf";
    fonts[EFont::RECKONER_BOLD] = "Fonts/Reckoner_Bold.ttf";
    fonts[EFont::RECKONER] = "Fonts/Reckoner.ttf";
    fonts[EFont::SANSATION] = "Fonts/Sansation.ttf";

    music[EMusic::MAIN] = loadMusic("Audio/Music/Crash_WarpRoomTheme.ogg", true);
    music[EMusic::GAME] = loadMusic("Audio/Music/GameTheme_2.ogg", true);
    music[EMusic::GAME_OVER] = loadMusic("Audio/Music/gameOverTheme.ogg", false);
    /** Todo: set volume */

    backgrounds[EBackground::TUTORIAL] = loadTexture("Textures/TutorialBackground2.png");
    backgrounds[EBackground::GAME1] = loadTexture("Textures/GameBackground_1.png");
    backgrounds[EBackground::GAME2] = loadTexture("Textures/GameBackground_2.jpg");
    backgrounds[EBackground::GAME3] = loadTexture("Textures/GameBackground_3.png");
    backgrounds[EBackground::VICTORY] = loadTexture("Textures/VictoryScreenBackground.png");

    maps[EMap::TEXTURE] = "Maps/map1.txt";
    maps[EMap::COLLISION] = "Maps/colmap1.txt";
}

Font AssetService::getFont(EFont font, int fontSize)
{
    std::string fontUrl = getFontUrl(font);
    Font fnt = LoadFontEx(fontUrl.c_str(), fontSize, 0, 0);
    SetTextureFilter(fnt.texture, TEXTURE_FILTER_BILINEAR);
    return fnt;
}

Texture2D AssetService::loadTexture(std::string filename)
{
    Texture2D texture = LoadTexture((assetDir + filename).c_str());
    return texture;
}

std::string AssetService::getFontUrl(EFont font)
{
    return assetDir + fonts[font];
}

Music AssetService::loadMusic(std::string filename, bool loops)
{
    Music music = LoadMusicStream((assetDir + filename).c_str());
    music.looping = loops;
    return music;
}

Sound AssetService::loadSound(std::string filename)
{
    Sound sound = LoadSound((assetDir + filename).c_str());
    return sound;
}
