#pragma once
#include "ECS/Component.h"
#include "Animation.h"


class Animator : public Component {
public:
    void Play(std::shared_ptr<Animation> animation);
    void Stop();
    void Update(float deltaTime);

private:
    std::shared_ptr<Animation> currentAnimation;
    float currentTime = 0.0f;
};
