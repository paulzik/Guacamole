#pragma once
#include "Assets/Asset.h"
#include <string>
#include <AL/al.h>

class AudioClip : public Asset {
public:
    AudioClip(const std::string& path);  // loads the file (MP3/WAV)
    ~AudioClip();

    ALuint getBuffer() const { return buffer; }

private:
    ALuint buffer = 0;
};