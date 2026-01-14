#pragma once
#include <AL/al.h>
#include <AL/alc.h>

class GuacAudio {
public:
    static bool Init();
    static void Shutdown();

private:
    static ALCdevice* sDevice;
    static ALCcontext* sContext;
};