#pragma once
#include "Systems/System.h"
#include "ECS/Transform.h"
#include <vector>

class TransformSystem : public System {

    std::vector<Transform*> transforms;

    bool Init() override;
    void Update() override;
    void Shutdown() override;
};