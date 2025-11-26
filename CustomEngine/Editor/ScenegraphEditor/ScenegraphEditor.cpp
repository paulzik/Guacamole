#include "ScenegraphEditor.h"
#include <iostream>
#include <imgui.h>

ScenegraphEditor::ScenegraphEditor(Scenegraph* _scenegraph)
	:EditorWindow("Scenegraph"), scenegraph(_scenegraph)
{

}

ScenegraphEditor::~ScenegraphEditor() {

}

void ScenegraphEditor::Draw()
{
    ImGui::Begin(windowName);

    // Recursive function to draw nodes
    std::function<void(Entity*)> DrawNode = [&](Entity* entity)
        {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
            if (entity->GetChildren().empty())
                flags |= ImGuiTreeNodeFlags_Leaf;

            bool node_open = ImGui::TreeNodeEx((void*)entity, flags, "%s", entity->GetName());

            if (node_open)
            {
                for (auto& child : entity->GetChildren())
                    DrawNode(child);

                ImGui::TreePop();
            }
        };

    // Start from root entities
    for (auto& root : scenegraph->GetRoots())
        DrawNode(root);

    ImGui::End();
}
