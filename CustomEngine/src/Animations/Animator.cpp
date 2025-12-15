#include "Animator.h"
#include <memory>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

void Animator::Start()
{
    if (!model) return;

    for (const auto& anim : model->animations) {

        std::cout << anim->GetAnimationName() << std::endl;
    }

    if (model->animations.size() > 0) {
        currentAnimation = model->animations[0];
        Play(currentAnimation);
    }
}

void Animator::Update()
{
    //FIX THIS
    Update(1.0f);
}

void Animator::Update(float deltaTime)
{
    if (!model || animations.empty())
        return;

    // Advance current animation time
    if (!currentAnimation) return;
    currentAnimationTime += deltaTime * currentAnimation->GetSpeed();

    // Loop animation if needed
    float animationDuration = currentAnimation->GetDuration();
    if (currentAnimationTime > animationDuration)
        currentAnimationTime = fmod(currentAnimationTime, animationDuration);

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
}

void Animator::Play(std::shared_ptr<Animation> animation)
{
    currentAnimation = animation;
    currentAnimationTime = 0.0f;
    animation->Play();
}


const char* Animator::GetComponentName() const
{
    return "Animator";
}