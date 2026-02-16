#pragma once
#include "Systems/System.h"
#include "ECS/Camera/Camera.h"
#include <vector>

class CameraSystem : public System {
    Camera* mainCamera;

    void TryRegister(Component* c) override;

    bool Init() override;
    void Update() override;
    void Shutdown() override;
};