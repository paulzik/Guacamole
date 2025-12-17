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

void Animator::Update()
{
    //FIX THIS
    Update(1.0f);
}

void Animator::Update(float deltaTime)
{
    if (model == nullptr) {
        std::cout << "MODEL" << std::endl;
    }

    if (currentAnimation == nullptr) {
        std::cout << "ANIM" << std::endl;

    }

    if (!model || !currentAnimation)
        return;

    // Advance current animation time
    if (!currentAnimation) return;
    //currentAnimationTime += deltaTime;

    // Loop animation if needed
    float animationDuration = currentAnimation->GetDuration();
    if (currentAnimationTime > animationDuration) {
        if (loop)
            currentAnimationTime = fmod(currentAnimationTime, animationDuration);
        else
            currentAnimationTime = animationDuration;
    }

    // Update all bones in the skeleton
    auto skeleton = model->skeleton;
    if (!skeleton) return;

    for (int boneIndex = 0; boneIndex < skeleton->GetBoneCount(); ++boneIndex)
    {
        glm::vec3 pos = currentAnimation->GetInterpolatedPosition(boneIndex, currentAnimationTime);
        glm::quat rot = currentAnimation->GetInterpolatedRotation(boneIndex, currentAnimationTime);
        glm::vec3 scale = currentAnimation->GetInterpolatedScale(boneIndex, currentAnimationTime);

        // Build local transform for this bone
        glm::mat4 localTransform = glm::translate(glm::mat4(1.0f), pos) *
            glm::mat4_cast(rot) *
            glm::scale(glm::mat4(1.0f), scale);

        skeleton->SetLocalBoneTransform(boneIndex, localTransform);
    }

    // After all bones are updated, compute final global transforms
    skeleton->ComputeGlobalTransforms();

    currentNormalizedTime = currentAnimation ? (currentAnimationTime / currentAnimation->GetDuration()) : 0.0f;
}

void Animator::Play(std::shared_ptr<Animation> animation)
{
    currentAnimation = animation;
    currentAnimationTime = 0.0f;
}


const char* Animator::GetComponentName() const
{
    return "Animator";
}

float Animator::GetCurrentAnimationTime()
{
    return currentAnimationTime;
}

void Animator::SetCurrentAnimationTime(float time)
{
    currentAnimationTime = time;
}

const std::vector<std::shared_ptr<Animation>>& Animator::GetAnimations() const
{
    return animations;
}

int Animator::GetCurrentAnimationIndex() const
{
    return currentAnimationIndex;
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

float Animator::GetCurrentAnimationDuration() const
{
    if (!currentAnimation)
        return 0.0f;

    return currentAnimation->GetDuration();
}

bool Animator::IsLooping() const
{
    return loop;
}

void Animator::SetLooping(bool _loop)
{
    loop = _loop;
}

std::shared_ptr<Model> Animator::GetModel()
{
    return model;
}
