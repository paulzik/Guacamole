#pragma once
#include "ECS/Component.h"
#include "AudioClip.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <memory>
#include <vector>
#include "glm/vec3.hpp"
class Transform;
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
    void SetPitch(float _pitch);
    void SetClip(std::shared_ptr<AudioClip> _clip);

    float GetPitch() const;
    bool GetLoop() const;
    float GetVolume() const;
    std::shared_ptr<AudioClip> GetAudioClip() const;

    bool IsPlaying() const;

    const char* GetComponentName() const override;
    void Start() override;
    void Update() override;

private:
    ALuint source = 0;
    std::shared_ptr<AudioClip> clip;

    float volume = 1.0f;
    float pitch = 1.0f;
    bool loop = false;
    Transform* transform = nullptr;
    glm::vec3 prevPosition;
    glm::vec3 currentPosition;
};