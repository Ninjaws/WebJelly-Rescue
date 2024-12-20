#ifndef ASSET_SERVICE_H
#define ASSET_SERVICE_H

#include "raylib.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "enums/EFont.h"
#include "enums/EMusic.h"
#include "enums/EBackground.h"
#include "enums/EMap.h"
#include "enums/ESprite.h"
#include "enums/ESound.h"
#include "services/Service.h"

class AssetService: public Service<AssetService>
{
public:
    void setAssetDir(std::string assetDir){this->assetDir = assetDir;}

    Font getFont(EFont font, int fontSize);
    Music getMusic(EMusic music) {
        return this->music[music];
    }
    Texture2D getBackground(EBackground background){
        return this->backgrounds[background];
    }
    Texture2D loadTexture(std::string filename);
    std::string getMapUrl(EMap map) {
        return this->assetDir + this->maps[map];
    }
    Texture2D getSprite(ESprite sprite) {
        return this->sprites[sprite];
    }

    void playSound(ESound sound) {
     PlaySound(sounds[sound]);
    }

protected:
    AssetService();

private:
    /** Friend to allow access to the constructor */
    friend class Service<AssetService>;

    std::string assetDir;
    std::unordered_map<EFont, std::string> fonts;
    std::unordered_map<ESound, Sound> sounds;
    std::unordered_map<EMusic, Music> music;
    std::unordered_map<EBackground, Texture2D> backgrounds;
    std::unordered_map<EMap, std::string> maps;
    std::unordered_map<ESprite, Texture2D> sprites;

    void setAssets();

    Music loadMusic(std::string filename, bool loops);
    Sound loadSound(std::string filename);
    std::string getFontUrl(EFont font);
};

#endif