#pragma once

#include "raylib.h"

class AudioManager
{
public:

    void Update();

    void InitAudio();
    void CloseAudio();
    void PlayLaserSound();
    void PlayExplosionSound();

    Music backgroundMusic;
    Sound laserSound;
    Sound explosionSound;
};