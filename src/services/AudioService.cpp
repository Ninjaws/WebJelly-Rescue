#include "services/AudioService.h"
#include "services/AssetService.h"

// AudioService::~AudioService()
// {
//     if (!music.has_value())
//         return;
//     UnloadMusicStream(music.value());
// }

void AudioService::setMusic(EMusic music)
{
    if (currentTrack == music)
        return;

    stopMusic(); // Makes sure it doesn't continue where it left off
    this->currentTrack = music;
    this->music = AssetService::getInstance().getMusic(music);
}

void AudioService::playMusic()
{
    if (!music.has_value())
        return;
    PlayMusicStream(music.value());
}

void AudioService::pauseMusic()
{
    if (!music.has_value())
        return;
    PauseMusicStream(music.value());
}

void AudioService::stopMusic()
{
    if (music.has_value())
    {
        StopMusicStream(music.value());
    }
    this->currentTrack = EMusic::NONE;
}

void AudioService::playSound()
{
}

void AudioService::stopSounds()
{
}
