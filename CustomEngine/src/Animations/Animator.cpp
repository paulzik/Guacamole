#include "Animator.h"
#include <memory>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

void Animator::Start()
{
    if (!model) return;

    animations = model->animations;

    for (const auto& anim : animations)
        std::cout << anim->GetAnimationName() << std::endl;

    if (!animations.empty())
        PlayByIndex(0);
}

void Animator::Play(std::shared_ptr<Animation> animation)
{
    currentAnimation = animation;
    currentAnimationTime = 0.0f;
}

void Animator::PlayByIndex(int index)
{
    if (index < 0 || index >= static_cast<int>(animations.size()))
    {
        std::cout << "Animator::PlayByIndex - invalid index: " << index << std::endl;
        return;
    }

    currentAnimationIndex = index;
    currentAnimation = animations[index];
    currentAnimationTime = 0.0f;
}

void Animator::SetCurrentAnimationIndex(int index)
{
    if (index < 0 || index >= static_cast<int>(animations.size()))
        return;

    currentAnimationIndex = index;
    currentAnimation = animations[index];
    currentAnimationTime = 0.0f;
}