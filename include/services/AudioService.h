#ifndef AUDIO_SERVICE_H
#define AUDIO_SERVICE_H

#include "raylib.h"
#include "enums/EMusic.h"
#include "services/Service.h"
#include <optional>

class AudioService : public Service<AudioService>
{
public:
    void setMusic(EMusic music);
    std::optional<Music> getMusic(){return music;}
    EMusic getCurrentTrack(){return currentTrack;}
    void playMusic();
    void pauseMusic();
    void stopMusic();

    void playSound();
    void stopSounds();

protected:

private:
    std::optional<Music> music;
    EMusic currentTrack = EMusic::NONE;

};

#endif