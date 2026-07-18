#pragma once
#include "ECS/Component.h"
#include "Animation.h"
#include "Assets/Model.h"
#include <vector>

struct Animator : public Component {

    std::shared_ptr<Model> model;
    std::vector<std::shared_ptr<Animation>> animations;

    std::shared_ptr<Animation> currentAnimation;
    int currentAnimationIndex = -1;

    float currentAnimationTime = 0.0f;
    bool loop = true;

    float currentNormalizedTime = 0.0f;

    Animator() = default;
    Animator(std::shared_ptr<Model> _model) : model(std::move(_model)) {}

    void Play(std::shared_ptr<Animation> animation);
    void Stop();
    void Start() override;

    void PlayByIndex(int index);
    void SetCurrentAnimationIndex(int index);

    COMPONENT_NAME(Animation);
};
