#include "InspectorWindow.h"
#include "ECS/Entity.h"
#include "EditorRegistry.h"
#include "imgui.h"
#include "SelectedEntity.h"

InspectorWindow::InspectorWindow()
    : EditorWindow("Inspector")
{
}

void InspectorWindow::Draw() {
    ImGui::Begin(windowName);

    Entity* entity = SelectedEntity::Get();
    if (!entity) {
        ImGui::Text("No entity selected.");
        ImGui::End();
        return;
    }

    ImGui::Text("Entity: %s", entity->GetName());

    // Draw all components for this entity
    for (Component* c : entity->GetComponents<Component>()) {
        if (ImGui::CollapsingHeader(c->GetComponentName())) {

            ComponentEditor* editor =
                EditorRegistry::Instance().CreateEditorFor(c);

            if (editor) {
                editor->Draw(c);
                delete editor;
            }
            else {
                ImGui::Text("No editor registered.");
            }
        }
    }

    ImGui::End();
}
