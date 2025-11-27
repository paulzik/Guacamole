#include "CameraEditor.h"
#include "EditorMacro.h"
#include "ECS/Camera.h"
#include <glm/gtc/type_ptr.hpp>

void CameraEditor::Draw(Component* component) {
    Camera* camera = static_cast<Camera*>(component);

    float fov = camera->GetFov();
    if(ImGui::SliderFloat("Field of View", &fov, 1.0f, 180.0f)) {
        camera->SetFov(fov);
    }

    float nearPlane = camera->GetNearPlane();
    if (ImGui::DragFloat("Near Plane", &nearPlane, 0.1f, 1.0f, 180.0f)) {
        camera->SetNearPlane(nearPlane);
    }

    float farPlane = camera->GetFarPlane();
    if (ImGui::DragFloat("Far Plane", &farPlane, 0.1f, 1.0f, 1000.0f)) {
        camera->SetFarPlane(farPlane);
    }

}

CUSTOM_EDITOR(Camera, CameraEditor);
