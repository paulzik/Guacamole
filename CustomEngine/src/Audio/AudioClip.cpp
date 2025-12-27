#include "AudioClip.h"
#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>

// Include minimp3 implementation
#define MINIMP3_IMPLEMENTATION
#define MINIMP3_EX_IMPLEMENTATION
#include "minimp3_ex.h"

AudioClip::AudioClip(const std::string& path)
{
    mp3dec_t mp3d;
    mp3dec_file_info_t info;

    if (mp3dec_load(&mp3d, path.c_str(), &info, NULL, NULL)) {
        std::cerr << "Failed to load mp3: " << path << std::endl;
        return;
    }

    // Determine OpenAL format
    if (info.channels == 1) format = AL_FORMAT_MONO16;
    else if (info.channels == 2) format = AL_FORMAT_STEREO16;
    else {
        std::cerr << "Unsupported channel count: " << info.channels << std::endl;
        free(info.buffer);  // free memory allocated by mp3dec_load
        return;
    }

    freq = info.hz;

    // Copy data to vector
    audioData.assign(reinterpret_cast<char*>(info.buffer),
        reinterpret_cast<char*>(info.buffer) + info.samples * info.channels * sizeof(mp3d_sample_t));

    // Generate OpenAL buffer
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, audioData.data(), static_cast<ALsizei>(audioData.size()), freq);

    free(info.buffer);
}

AudioClip::~AudioClip()
{
    if (buffer != 0) alDeleteBuffers(1, &buffer);
}

ALuint AudioClip::GetBuffer() const
{
    return buffer;
}