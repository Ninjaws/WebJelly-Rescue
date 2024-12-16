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
    music[EMusic::GAME_OVER] = loadMusic("Audio/Music/gameOverTheme_2.ogg", false);
    /** Todo: set volume */

    sounds[ESound::SHOOT] = loadSound("Audio/Sounds/gunShot.wav");
    SetSoundVolume(sounds[ESound::SHOOT], 0.4f);
    sounds[ESound::NO_AMMO] = loadSound("Audio/Sounds/outOfAmmo.wav");
    sounds[ESound::CRATE_BREAK] = loadSound("Audio/Sounds/crateBreak.wav");
    sounds[ESound::JELLY_FREED] = loadSound("Audio/Sounds/jellyFreed.wav");
    sounds[ESound::HEAL_PICKUP] = loadSound("Audio/Sounds/healmag.wav");
    sounds[ESound::AMMO_PICKUP] = loadSound("Audio/Sounds/shotgunReload.wav");
    sounds[ESound::POWERUP] = loadSound("Audio/Sounds/powerUpSound.wav");
    sounds[ESound::VICTORY] = loadSound("Audio/Sounds/victorySound.wav");
    sounds[ESound::PLAYER_DAMAGE] = loadSound("Audio/Sounds/WaterBalloon.wav");
    sounds[ESound::ENEMY_DEFEATED] = loadSound("Audio/Sounds/pain.wav");

    backgrounds[EBackground::TUTORIAL] = loadTexture("Textures/TutorialBackground2.png");
    backgrounds[EBackground::GAME1] = loadTexture("Textures/GameBackground_1.png");
    backgrounds[EBackground::GAME2] = loadTexture("Textures/GameBackground_2.jpg");
    backgrounds[EBackground::GAME3] = loadTexture("Textures/GameBackground_3.png");
    backgrounds[EBackground::VICTORY] = loadTexture("Textures/VictoryScreenBackground.png");

    maps[EMap::TEXTURE] = "Maps/map1.txt";
    maps[EMap::COLLISION] = "Maps/colmap1.txt";

    sprites[ESprite::PLAYER] = loadTexture("Textures/player.png");
    sprites[ESprite::PLAYER_GUN_LEFT] = loadTexture("Textures/gunleft.png");
    sprites[ESprite::PLAYER_GUN_RIGHT] = loadTexture("Textures/gunright.png");
    sprites[ESprite::ENEMY] = loadTexture("Textures/enemy.png");
    sprites[ESprite::ENEMY_GUN_LEFT] = loadTexture("Textures/gunleft_2.png");
    sprites[ESprite::ENEMY_GUN_RIGHT] = loadTexture("Textures/gunright_2.png");
    sprites[ESprite::CRATE] = loadTexture("Textures/woodencrate.png");
    sprites[ESprite::JELLY] = loadTexture("Textures/happyjelly.png");
    sprites[ESprite::HEALTHPACK] = loadTexture("Textures/FirstAidKit.png");
    sprites[ESprite::AMMOPACK] = loadTexture("Textures/Bullets_small.png");
    sprites[ESprite::POWERUP] = loadTexture("Textures/powerUpAnimation.png");
    sprites[ESprite::HUD_HEART] = loadTexture("Textures/heart.png");
    sprites[ESprite::HUD_HEART_EMPTY] = loadTexture("Textures/heart_empty.png");
    sprites[ESprite::HUD_AMMO] = loadTexture("Textures/bullet_hud.png");
    sprites[ESprite::CROSSHAIR] = loadTexture("Textures/crosshair_3.png");
    sprites[ESprite::FLAG] = loadTexture("Textures/flag.png");
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
