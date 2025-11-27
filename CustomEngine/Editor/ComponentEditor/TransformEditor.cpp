#include "TransformEditor.h"
#include "EditorMacro.h"
#include <glm/gtc/type_ptr.hpp>

void TransformEditor::Draw(Component* component) {
    Transform* transform = static_cast<Transform*>(component);

    glm::vec3 pos = transform->GetPosition();
    if (ImGui::DragFloat3("Position", glm::value_ptr(pos), 0.1f, 0.0f, 0.0f)) {
        transform->SetPosition(pos);
    }

    glm::vec3 rot = transform->GetRotationEuler();
    if (ImGui::DragFloat3("Rotation", glm::value_ptr(rot), 0.1f, 0.0f, 0.0f)) {
        transform->SetRotation(rot);
    }

    glm::vec3 sc = transform->GetScale();
    if (ImGui::DragFloat3("Scale", glm::value_ptr(sc), 0.1f, 0.0f, 0.0f)) {
        transform->SetScale(sc);
    }

}

CUSTOM_EDITOR(Transform, TransformEditor);
