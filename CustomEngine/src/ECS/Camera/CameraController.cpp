#include "CameraController.h"
#include "Input/Input.h"
#include "ECS/Entity.h"

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
        //Camera Rotation
        glm::vec2 delta = mouse->mouseDelta;
        glm::vec3 euler = glm::degrees(glm::eulerAngles(transformComp->rotation));

        float pitch = euler.x;
        float yaw = euler.y;

        yaw += -delta.x * sensitivity;
        pitch -= delta.y * sensitivity;

        pitch = glm::clamp(pitch, -89.0f, 89.0f);

        glm::quat qYaw = glm::angleAxis(glm::radians(yaw), glm::vec3(0, 1, 0));
        glm::quat qPitch = glm::angleAxis(glm::radians(pitch), glm::vec3(1, 0, 0));

        transformComp->rotation = qYaw * qPitch;

        //Camera Translation WASD
        if (keyboard->wKey().isDown) {
            //transformComp->position += transformComp * speed * deltaTime;
        }
    }


    //Camera Translation
    if (keyboard->leftAltKey().isDown) {
        //Left click Gaze focus point

        //Right click zoom in-out

    }
}

