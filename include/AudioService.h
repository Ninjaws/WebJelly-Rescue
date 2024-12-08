#ifndef AUDIO_SERVICE_H
#define AUDIO_SERVICE_H

#include "raylib.h"
#include "EMusic.h"
#include "Service.h"
#include <optional>

class AudioService : public Service<AudioService>
{
private:
    std::optional<Music> music;
    EMusic currentTrack = EMusic::NONE;

protected:

public:
    void setMusic(EMusic music);
    std::optional<Music> getMusic(){return music;}
    EMusic getCurrentTrack(){return currentTrack;}
    void playMusic();
    void pauseMusic();
    void stopMusic();

    void playSound();
    void stopSounds();
};

#endif