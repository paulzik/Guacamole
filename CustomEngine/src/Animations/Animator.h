#pragma once
#include "ECS/Component.h"
#include "Animation.h"
#include "Assets/Model.h"
#include <vector>

class Animator : public Component {
public:
    void Play(std::shared_ptr<Animation> animation);
    void Stop();

    void Start() override;
    void Update() override;
    void Update(float deltaTime);

    const char* GetComponentName() const override;

    Animator(std::shared_ptr<Model> m) : model(m) {}
private:
    std::vector<std::shared_ptr<Animation>> animations;
    std::shared_ptr<Animation> currentAnimation;
    std::shared_ptr<Model> model;

    float currentAnimationTime = 0.0f;
};
