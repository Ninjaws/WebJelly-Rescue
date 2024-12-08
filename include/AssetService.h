#ifndef ASSET_SERVICE_H
#define ASSET_SERVICE_H

#include "raylib.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "EFont.h"
#include "EMusic.h"
#include "EBackground.h"
#include "Service.h"

class AssetService: public Service<AssetService>
{
private:
    /** Friend to allow access to the constructor */
    friend class Service<AssetService>;

    std::string assetDir;
    std::unordered_map<EFont, std::string> fonts;
    std::vector<Sound> sounds;
    std::unordered_map<EMusic, Music> music;
    std::unordered_map<EBackground, Texture2D> backgrounds;

    void setAssets();

    Music loadMusic(std::string filename, bool loops);
    Sound loadSound(std::string filename);
    std::string getFontUrl(EFont font);
protected:
    AssetService();

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
};

#endif