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
    float GetCurrentAnimationTime();
    void SetCurrentAnimationTime(float time);

    const std::vector<std::shared_ptr<Animation>>& GetAnimations() const;
    int  GetCurrentAnimationIndex() const;
    void PlayByIndex(int index);
    void SetCurrentAnimationIndex(int index);

    float GetCurrentAnimationDuration() const;

    bool  IsLooping() const;
    void  SetLooping(bool _loop);

    std::shared_ptr<Model> GetModel();

    Animator(std::shared_ptr<Model> m) : model(m) {}
private:
    std::shared_ptr<Model> model;
    std::vector<std::shared_ptr<Animation>> animations;

    std::shared_ptr<Animation> currentAnimation;
    int currentAnimationIndex = -1;

    float currentAnimationTime = 0.0f;
    bool loop = true;

    float currentNormalizedTime = 0.0f;
};
