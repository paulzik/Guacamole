#include "InspectorWindow.h"
#include "ECS/Entity.h"
#include "EditorRegistry.h"
#include "imgui.h"
#include <ECS/Scene.h>
#include <cstring>

InspectorWindow::InspectorWindow()
    : EditorWindow("Inspector")
{
}

void InspectorWindow::Draw() {

    if (!BeginWindow()) return;

    Entity* entity = Scene::Get().selectedEntity;
    if (!entity) {
        ImGui::Text("No entity selected.");
        ImGui::End();
        return;
    }

    // %s expects a const char* - passing std::string through varargs is UB.
    ImGui::Text("Entity: %s", entity->GetName().c_str());

    for (Component* c : entity->GetComponents<Component>()) {
        bool isTransform = std::strcmp(c->GetComponentName(), "Transform") == 0;

        bool keep = true;
        bool headerOpen = isTransform
            ? ImGui::CollapsingHeader(c->GetComponentName(), ImGuiTreeNodeFlags_DefaultOpen)
            : ImGui::CollapsingHeader(c->GetComponentName(), &keep, ImGuiTreeNodeFlags_DefaultOpen);

        if (!keep) {
            entity->RemoveComponent(c);
            continue;
        }

        if (headerOpen) {
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
