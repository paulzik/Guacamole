#include "ScenegraphEditor.h"
#include <iostream>
#include <imgui.h>
#include "ECS/Scene.h"

ScenegraphEditor::ScenegraphEditor(Scenegraph* _scenegraph)
	:EditorWindow("Scenegraph"), scenegraph(_scenegraph)
{

}

ScenegraphEditor::~ScenegraphEditor() {

}

void ScenegraphEditor::Draw()
{
    if (!BeginWindow()) return;

    Entity* selected = Scene::Get().selectedEntity;

    //True if 'possibleAncestor' is a parent (direct or indirect) of 'entity'
    auto IsAncestorOf = [](Entity* possibleAncestor, Entity* entity)
        {
            for (Entity* p = entity->GetParent(); p != nullptr; p = p->GetParent())
                if (p == possibleAncestor)
                    return true;
            return false;
        };

    // Recursive function to draw nodes
    std::function<void(Entity*)> DrawNode = [&](Entity* entity)
        {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
            if (entity->GetChildren().empty())
                flags |= ImGuiTreeNodeFlags_Leaf;

            if (entity == selected)
                flags |= ImGuiTreeNodeFlags_Selected;

            //Expand ancestors so a selection made in the viewport is visible
            if (selected && IsAncestorOf(entity, selected))
                ImGui::SetNextItemOpen(true);

            bool node_open = ImGui::TreeNodeEx((void*)entity, flags, "%s", entity->GetName());

            if (ImGui::IsItemClicked())
            {
                Scene::Get().selectedEntity = entity;
            }

            if (node_open)
            {
                for (auto& child : entity->GetChildren())
                    DrawNode(child);

                ImGui::TreePop();
            }
        };

    for (auto& root : scenegraph->GetRoots())
        DrawNode(root);

    ImGui::End();
}
