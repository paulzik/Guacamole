#pragma once
#include "Systems/System.h"
#include "ECS/Transform.h"
#include <vector>

class TransformSystem : public System {   
public:
    bool Init() override;
    void Update() override;
    void Shutdown() override;
};