#include "ColliderEditor.h"
#include "EditorMacro.h"
#include <imgui_impl_opengl3.h>

void ColliderEditor::Draw(Component* component) {
    Collider* col = static_cast<Collider*>(component);

    bool isTrigger = col->isTrigger;
    if (ImGui::Checkbox("IsTrigger", &isTrigger))
    {
        col->isTrigger = isTrigger;
    }
}

CUSTOM_EDITOR(Collider, ColliderEditor);