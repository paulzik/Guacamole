#include "TransformEditor.h"
#include "EditorMacro.h"

void TransformEditor::Draw(Component* component) {
    Transform* t = static_cast<Transform*>(component);

    glm::vec3 pos = t->getPosition();
    if (ImGui::InputFloat3("Position", &pos.x)) {
        t->setPosition(pos);
    }

}

CUSTOM_EDITOR(Transform, TransformEditor);
