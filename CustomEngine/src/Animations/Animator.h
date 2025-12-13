#pragma once
#include "ECS/Component.h"
#include "Animation.h"


class Animator : public Component {
public:
    void Play(std::shared_ptr<Animation> animation);
    void Stop();
    void Update(float deltaTime);

    const char* GetComponentName() const override;

private:
    std::shared_ptr<Animation> currentAnimation;
};
