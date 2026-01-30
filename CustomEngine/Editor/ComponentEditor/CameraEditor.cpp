#include "CameraEditor.h"
#include "EditorMacro.h"
#include "ECS/Camera.h"
#include <glm/gtc/type_ptr.hpp>

void CameraEditor::Draw(Component* component) {
    Camera* camera = static_cast<Camera*>(component);

    float fov = glm::degrees(camera->fov);
    if(ImGui::SliderFloat("Field of View", &fov, 1.0f, 180.0f)) {
        camera->fov = glm::radians(fov);
    }

    float nearPlane = camera->nearPlane;
    if (ImGui::DragFloat("Near Plane", &nearPlane, 0.1f, 1.0f, 180.0f)) {
        camera->nearPlane = nearPlane;
    }

    float farPlane = camera->farPlane;
    if (ImGui::DragFloat("Far Plane", &farPlane, 0.1f, 1.0f, 1000.0f)) {
        camera->farPlane = farPlane;
    }
}

CUSTOM_EDITOR(Camera, CameraEditor);
