#pragma once
#include "Assets/Asset.h"
#include <vector>
#include <AL/al.h>

class AudioClip : public Asset {
public:
    AudioClip(const std::string& path);
    ~AudioClip();

    ALuint GetBuffer() const;

private:
    ALuint buffer = 0;
    std::vector<char> audioData;
    ALenum format = 0;
    ALsizei freq = 0;
};