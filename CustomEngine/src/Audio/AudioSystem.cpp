#include "AudioSystem.h"
#include <iostream>
#include <ECS/Transform.h>
#include "ECS/Entity.h"
#include <ECS/TransformUtils.h>

void AudioSystem::TryRegister(Component* c)
{
    if (!audioListener) {
        if (auto aL = dynamic_cast<AudioListener*>(c)) {
            audioListener = aL;
            audioListenerTransform = audioListener->owner->TryGetComponent<Transform>();
            return;
        }
    }

    if (auto aS = dynamic_cast<AudioSource*>(c)) {
        audioSources.push_back(aS);
        return;
    }
}

bool AudioSystem::Init()
{
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

void AudioSystem::Update()
{
    UpdateAudioListener();

}

void AudioSystem::UpdateAudioSources()
{
    for (AudioSource* source : audioSources) {
        if (!source->owner || !source->transform)
            continue;

        source->currentPosition = source->transform->position;

        if (source->currentPosition != source->prevPosition)
        {
            alSource3f(source->source, AL_POSITION,
                source->currentPosition.x,
                source->currentPosition.y,
                source->currentPosition.z);

            source->prevPosition = source->currentPosition;
        }
    }
}

void AudioSystem::UpdateAudioListener()
{
    if (!audioListener)
        return;

    // Position
    glm::vec3 pos = audioListenerTransform->position;
    alListener3f(AL_POSITION, pos.x, pos.y, pos.z);

    // Orientation (forward + up)
    glm::vec3 forward = GetForward(*audioListenerTransform);
    glm::vec3 up = audioListenerTransform->up;

    float orientation[6] = {
        forward.x, forward.y, forward.z,
        up.x,      up.y,      up.z
    };

    alListenerfv(AL_ORIENTATION, orientation);
}


void AudioSystem::Shutdown()
{
    for (AudioSource* audioSource : audioSources)
    {
        if (audioSource->source != 0)
            alDeleteSources(1, &audioSource->source);
    }

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
