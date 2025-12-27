#pragma once
#include "Assets/Asset.h"
#include <string>
#include <AL/al.h>

class AudioClip : public Asset {
public:
    AudioClip(const std::string& path);
    ~AudioClip();

    ALuint GetBuffer() const;

private:
    ALuint buffer = 0;
};