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
    void SetLoop(bool _loop);
    void SetVolume(float _volume);
    void SetPosition(glm::vec3 _position);
    void SetPitch(float _pitch);
    void SetClip(std::shared_ptr<AudioClip> _clip);

    glm::vec3 GetPosition();
    float GetPitch();
    bool GetLoop();
    float GetVolume();
    std::shared_ptr<AudioClip> GetAudioClip();

    bool IsPlaying() const;

    const char* GetComponentName() const override;

private:
    ALuint source = 0;
    std::shared_ptr<AudioClip> clip;

    float volume = 1.0f;
    float pitch = 1.0f;
    bool loop = false;
    glm::vec3 position;
};