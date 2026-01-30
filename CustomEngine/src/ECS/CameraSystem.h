#pragma once
#include "Systems/System.h"
#include "ECS/Camera.h"
#include <vector>

class CameraSystem : public System {

    bool Init() override;
    void Update() override;
    void Shutdown() override;
};