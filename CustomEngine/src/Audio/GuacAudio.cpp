#include "GuacAudio.h"
#include <iostream>

ALCdevice* GuacAudio::sDevice = nullptr;
ALCcontext* GuacAudio::sContext = nullptr;

bool GuacAudio::Init() {
    sDevice = alcOpenDevice(nullptr);
    if (!sDevice) {
        std::cerr << "Failed to open OpenAL device!" << std::endl;
        return false;
    }

    sContext = alcCreateContext(sDevice, nullptr);
    if (!sContext || !alcMakeContextCurrent(sContext)) {
        std::cerr << "Failed to create or set OpenAL context!" << std::endl;
        if (sContext) alcDestroyContext(sContext);
        alcCloseDevice(sDevice);
        return false;
    }
    alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
    return true;
}

void GuacAudio::Shutdown() {
    if (sContext) {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(sContext);
        sContext = nullptr;
    }
    if (sDevice) {
        alcCloseDevice(sDevice);
        sDevice = nullptr;
    }
}
