#pragma once
#include "Assets/Asset.h"
#include <vector>
#include <AL/al.h>
#include <string>

class AudioClip : public Asset {
public:
    AudioClip(const std::string& path);
    ~AudioClip();

    const std::string GetAudioName();

    ALuint GetBuffer() const;

private:
    ALuint buffer = 0;
    std::vector<char> audioData;
    ALenum format = 0;
    ALsizei freq = 0;

    std::string audioPath;
    std::string audioName;
};