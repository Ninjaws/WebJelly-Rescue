#ifndef AUDIO_SERVICE_H
#define AUDIO_SERVICE_H

#include "raylib.h"
#include "EMusic.h"
#include "Service.h"
#include <optional>

class AudioService : public Service<AudioService>
{
private:
    /** Friend to allow access to the destructor */
    // friend class Service<AudioService>;
    std::optional<Music> music;
    EMusic currentTrack;

protected:
    // ~AudioService();

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