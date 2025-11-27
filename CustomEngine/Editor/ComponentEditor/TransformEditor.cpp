#include "TransformEditor.h"
#include "EditorMacro.h"
#include <glm/gtc/type_ptr.hpp>

void TransformEditor::Draw(Component* component) {
    Transform* transform = static_cast<Transform*>(component);

    glm::vec3 pos = transform->GetPosition();
    if (ImGui::InputFloat3("Position", glm::value_ptr(pos))) {
        transform->SetPosition(pos);
    }

    glm::vec3 rot = transform->GetRotationEuler();
    if (ImGui::InputFloat3("Rotation", glm::value_ptr(rot))) {
        transform->SetRotation(rot);
    }

    glm::vec3 sc = transform->GetScale();
    if (ImGui::InputFloat3("Scale", glm::value_ptr(sc))) {
        transform->SetScale(sc);
    }

}

CUSTOM_EDITOR(Transform, TransformEditor);
