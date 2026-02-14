#include "Headers/soundManager.hpp"


void AudioManager::InitAudio()
{
    backgroundMusic = LoadMusicStream("ost/music.ogg");
    PlayMusicStream(backgroundMusic);
    
    laserSound = LoadSound("ost/laser.ogg");
    explosionSound = LoadSound("ost/explosion.ogg");
}

void AudioManager::Update()
{
    UpdateMusicStream(backgroundMusic);
}

void AudioManager::CloseAudio()
{
    UnloadMusicStream(backgroundMusic);
    UnloadSound(laserSound);
    UnloadSound(explosionSound);
}

void AudioManager::PlayLaserSound()
{
    PlaySound(laserSound);
}

void AudioManager::PlayExplosionSound()
{
    PlaySound(explosionSound);
}
