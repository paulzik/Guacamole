#pragma once
#include "ECS/Component.h"
#include "AudioClip.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <memory>
#include <vector>
#include "glm/vec3.hpp"

class AudioSource : public Component
{
public:
    AudioSource();
    ~AudioSource();

    void Play();
    void Stop();
    void Pause();
    void SetLoop(bool loop);
    void SetVolume(float volume);
    void SetPosition(glm::vec3 position);
    void SetPitch(float pitch);
    void SetClip(std::shared_ptr<AudioClip> clip);

    glm::vec3 GetPosition();
    float GetPitch();
    bool GetLoop();
    float GetVolume();

    bool IsPlaying() const;

private:
    ALuint source = 0;
    std::shared_ptr<AudioClip> clip;

    float volume = 1.0f;
    float pitch = 1.0f;
    bool loop = false;
    glm::vec3 position;
};