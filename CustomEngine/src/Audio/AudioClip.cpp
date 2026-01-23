#include "AudioClip.h"
#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include <string>
#include "minimp3_ex.h"
#include <filesystem>

AudioClip::AudioClip(const std::string& path)
{
    mp3dec_t dec;
    mp3dec_file_info_t info;
    memset(&info, 0, sizeof(info));

    if (mp3dec_load(&dec, path.c_str(), &info, nullptr, nullptr)) {
        throw std::runtime_error("Failed to load MP3");
    }

    ALenum format = (info.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

    alGenBuffers(1, &buffer);
    alBufferData(
        buffer,
        format,
        info.buffer,
        info.samples * sizeof(mp3d_sample_t),
        info.hz
    );
    audioPath = path;
    audioName = std::filesystem::path(audioPath).filename().string();
}

AudioClip::~AudioClip()
{
    if (buffer != 0) alDeleteBuffers(1, &buffer);
}

const std::string AudioClip::GetAudioName()
{
    return audioName;
}

ALuint AudioClip::GetBuffer() const
{
    return buffer;
}