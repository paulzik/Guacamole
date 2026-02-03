#pragma once
#include <vector>
#include "Systems/System.h"
#include "Animator.h"

struct AnimationSystem : public System {
    std::vector<Animator*> animators;
    void TryRegister(Component* c) override;

    bool Init() override;
    void Update() override;
    void Shutdown() override;

    void UpdateAnimation(float deltaTime);
};
