#include "TransformEditor.h"
#include "EditorMacro.h"
#include <glm/gtc/type_ptr.hpp>
#include "ECS/TransformUtils.h"

void TransformEditor::Draw(Component* component) {
    Transform* transform = static_cast<Transform*>(component);

    glm::vec3 pos = transform->position;
    if (ImGui::DragFloat3("Position", glm::value_ptr(pos), 0.1f, 0.0f, 0.0f)) {
        transform->position = pos;
    }

    glm::vec3 rot = GetRotationEuler(*transform);
    if (ImGui::DragFloat3("Rotation", glm::value_ptr(rot), 0.1f, 0.0f, 0.0f)) {
        transform->rotation = glm::quat(rot);
    }

    glm::vec3 sc = transform->scale;
    if (ImGui::DragFloat3("Scale", glm::value_ptr(sc), 0.1f, 0.0f, 0.0f)) {
        transform->scale = sc;
    }

}

CUSTOM_EDITOR(Transform, TransformEditor);
