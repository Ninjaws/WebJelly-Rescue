#include "AssetService.h"
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
}

Font AssetService::getFont(EFont font, int fontSize)
{
    std::string fontUrl = getFontUrl(font);
    Font fnt = LoadFontEx(fontUrl.c_str(), fontSize, 0, 0);
    SetTextureFilter(fnt.texture, TEXTURE_FILTER_BILINEAR);
    return fnt;
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
