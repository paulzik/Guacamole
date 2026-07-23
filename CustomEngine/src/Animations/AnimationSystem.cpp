#include "AnimationSystem.h"
#include "Time/Time.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>

void AnimationSystem::TryRegister(Component* c)
{
    if (auto anim = dynamic_cast<Animator*>(c))
        animators.push_back(anim);
}

bool AnimationSystem::Init()
{
    for (auto animator : animators) {
        if (!animator->model || !animator->currentAnimation)
            continue;

        if (!animator->model->skeleton)
            continue;

        // Pose at the starting time so the model is correct even before it plays.
        ApplyPose(animator);
    }

	return true;
}

void AnimationSystem::ApplyPose(Animator* animator)
{
    auto skeleton = animator->model->skeleton;

    // Update all bones in the skeleton
    for (int boneIndex = 0; boneIndex < skeleton->GetBoneCount(); ++boneIndex)
    {
        //Bones the animation does not drive keep their bind pose
        if (!animator->currentAnimation->HasChannel(boneIndex))
        {
            skeleton->SetLocalBoneTransform(boneIndex, skeleton->GetBone(boneIndex).localBindPose);
            continue;
        }

        glm::vec3 pos = animator->currentAnimation->GetInterpolatedPosition(boneIndex, animator->currentAnimationTime);
        glm::quat rot = animator->currentAnimation->GetInterpolatedRotation(boneIndex, animator->currentAnimationTime);
        glm::vec3 scale = animator->currentAnimation->GetInterpolatedScale(boneIndex, animator->currentAnimationTime);

        // Build local transform for this bone
        glm::mat4 localTransform = glm::translate(glm::mat4(1.0f), pos) *
            glm::mat4_cast(rot) *
            glm::scale(glm::mat4(1.0f), scale);

        skeleton->SetLocalBoneTransform(boneIndex, localTransform);
    }

    // After all bones are updated, compute final global transforms
    skeleton->ComputeGlobalTransforms();
}

void AnimationSystem::Update()
{
    float deltaTime = Time::DeltaTime();

    for (auto animator : animators)
    {
        if (!animator->model || !animator->currentAnimation)
            continue;

        auto skeleton = animator->model->skeleton;
        if (!skeleton)
            continue;

        float animationDuration = animator->currentAnimation->GetDuration();

        if (animator->play)
        {
            animator->currentAnimationTime += deltaTime;

            // Loop animation if needed
            if (animator->currentAnimationTime > animationDuration) {
                if (animator->loop)
                    animator->currentAnimationTime = fmod(animator->currentAnimationTime, animationDuration);
                else
                    animator->currentAnimationTime = animationDuration;
            }
        }

        // Pose the skeleton at the current time, whether playing or paused.
        ApplyPose(animator);

        animator->currentNormalizedTime = animationDuration > 0.0f
            ? (animator->currentAnimationTime / animationDuration)
            : 0.0f;
    }
}

void AnimationSystem::Shutdown()
{
    animators.clear();
}
