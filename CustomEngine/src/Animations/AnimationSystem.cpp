#include "AnimationSystem.h"
#include <iostream>

void AnimationSystem::TryRegister(Component* c)
{
    if (auto anim = dynamic_cast<Animator*>(c))
        animators.push_back(anim);
}

bool AnimationSystem::Init()
{
	return false;
}

void AnimationSystem::Update()
{
    //MAKE THIS UPDATE ITSELF
    float deltaTime = 1.0f;

    for (auto animator : animators)
    {
        if (animator->model == nullptr) {
            std::cout << "MODEL" << std::endl;
        }

        if (animator->currentAnimation == nullptr) {
            std::cout << "ANIM" << std::endl;

        }

        if (!animator->model || !animator->currentAnimation)
            return;

        // Advance current animation time
        if (!animator->currentAnimation) return;
        animator->currentAnimationTime += deltaTime;

        // Loop animation if needed
        float animationDuration = animator->currentAnimation->GetDuration();
        if (animator->currentAnimationTime > animationDuration) {
            if (animator->loop)
                animator->currentAnimationTime = fmod(animator->currentAnimationTime, animationDuration);
            else
                animator->currentAnimationTime = animationDuration;
        }

        // Update all bones in the skeleton
        auto skeleton = animator->model->skeleton;
        if (!skeleton) return;

        for (int boneIndex = 0; boneIndex < skeleton->GetBoneCount(); ++boneIndex)
        {
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

        animator->currentNormalizedTime = animator->currentAnimation ? (animator->currentAnimationTime / animator->currentAnimation->GetDuration()) : 0.0f;
    }

}

void AnimationSystem::Shutdown()
{
    animators.clear();
}
