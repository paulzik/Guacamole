#pragma once
#include "ECS/Component.h"
#include "AudioClip.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <memory>
#include <vector>
#include "glm/vec3.hpp"
#include "ECS/Transform.h"

struct AudioSource : public Component
{
public:
    void Play();
    void Stop();
    void Pause();

    ALuint source = 0;
    std::shared_ptr<AudioClip> clip;

    float volume = 1.0f;
    float pitch = 1.0f;
    bool loop = false;
    Transform* transform = nullptr;
    glm::vec3 prevPosition;
    glm::vec3 currentPosition;

    COMPONENT_NAME(AudioSource);
};