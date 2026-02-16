#pragma once
#include "Input/Mouse.h"
#include "Input/Keyboard.h"
#include <ECS/Transform.h>

class CameraController : public Component
{
public:
    float sensitivity = 0.1f;
    float moveSpeed = 2.0f;

    void Start() override;
    void Update() override;

private:
    float pitch = 0.0f;
    float yaw = -90.0f;

    Mouse* mouse;
    Keyboard* keyboard;
    Transform* transformComp;

    COMPONENT_NAME(CameraController);
};