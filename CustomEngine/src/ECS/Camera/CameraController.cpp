#include "CameraController.h"
#include "Input/Input.h"
#include "ECS/Entity.h"
#include "Time/Time.h"

void CameraController::Start()
{
    mouse = Input::Input::GetDevice<Mouse>();
    keyboard = Input::Input::GetDevice<Keyboard>();

    transformComp = owner->TryGetComponent<Transform>();

    glm::vec3 euler = glm::degrees(glm::eulerAngles(transformComp->rotation));

    pitch = euler.x;
    yaw = euler.y;
}

void CameraController::Update()
{
    if (mouse->rightButton.isDown) {
        glm::vec2 delta = mouse->mouseDelta;

        yaw += -delta.x * sensitivity;
        pitch -= delta.y * sensitivity;

        pitch = glm::clamp(pitch, -89.0f, 89.0f);

        // Wrap yaw between 0-360° or -180° to 180° to prevent floating point overflow
        if (yaw > 360.0f) yaw -= 360.0f;
        else if (yaw < -360.0f) yaw += 360.0f;

        glm::quat qYaw = glm::angleAxis(glm::radians(yaw), glm::vec3(0, 1, 0));
        glm::quat qPitch = glm::angleAxis(glm::radians(pitch), glm::vec3(1, 0, 0));

        transformComp->rotation = qYaw * qPitch;

        glm::vec3 forward = glm::normalize(transformComp->rotation * glm::vec3(0, 0, -1));
        glm::vec3 right = glm::normalize(transformComp->rotation * glm::vec3(1, 0, 0));
        glm::vec3 up = glm::normalize(transformComp->rotation * glm::vec3(0, 1, 0));

        if (keyboard->wKey().isDown)
            transformComp->position += forward * moveSpeed * Time::DeltaTime();
        if (keyboard->sKey().isDown)
            transformComp->position -= forward * moveSpeed * Time::DeltaTime();
        if (keyboard->aKey().isDown)
            transformComp->position -= right * moveSpeed * Time::DeltaTime();
        if (keyboard->dKey().isDown)
            transformComp->position += right * moveSpeed * Time::DeltaTime();
        if (keyboard->qKey().isDown)
            transformComp->position += up * moveSpeed * Time::DeltaTime();
        if (keyboard->eKey().isDown)
            transformComp->position -= up * moveSpeed * Time::DeltaTime();
    }

    /*
    if (keyboard->leftAltKey().isDown) {

        //Left click Gaze focus point
        if (mouse->rightButton.isDown) {

        }
    }
    */
}

void CameraController::Destroy()
{
    // mouse, keyboard, and transformComp are not owned by this component — do not delete them
}

