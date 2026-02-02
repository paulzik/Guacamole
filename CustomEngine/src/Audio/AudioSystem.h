#pragma once
#include "Systems/System.h"
#include "AudioListener.h"
#include "AudioSource.h"
#include "ECS/Transform.h"
#include <AL/al.h>
#include <AL/alc.h>

class AudioSystem : public System {
public:
    void TryRegister(Component* c) override;

    bool Init() override;
    void Update() override;
    void Shutdown() override;

private:
    ALCdevice* sDevice;
    ALCcontext* sContext;

    AudioListener* audioListener;
    std::vector<AudioSource*> audioSources;

    Transform* audioListenerTransform;

    void UpdateAudioListener();
    void UpdateAudioSources();
};