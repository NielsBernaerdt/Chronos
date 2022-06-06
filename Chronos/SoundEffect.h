#pragma once
#include <string>
#include "SDL_mixer.h"

class SoundEffect
{
public:
    explicit SoundEffect(const std::string& path, std::string id, int loops = 0);
    ~SoundEffect();
    SoundEffect(const SoundEffect& other) = delete;
    SoundEffect& operator=(const SoundEffect& rhs) = delete;
    SoundEffect(SoundEffect&& other) = delete;
    SoundEffect& operator=(SoundEffect&& rhs) = delete;

    bool IsLoaded() const;
    bool Play(int loops, float volume);
    void SetVolume(int value);
    int GetVolume() const;
    static void StopAll();
    static void PauseAll();
    static void ResumeAll();
    std::string GetId() const { return id; }
private:
    Mix_Chunk* m_pMixChunk;
    std::string id{};
    int m_Loops{};
};