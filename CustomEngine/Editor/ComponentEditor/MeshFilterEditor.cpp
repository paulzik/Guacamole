#include "MeshFilterEditor.h"
#include "ECS/MeshFilter.h"
#include "EditorMacro.h"
#include <glm/gtc/type_ptr.hpp>
#include <string>

void MeshFilterEditor::Draw(Component* component) {
    MeshFilter* meshFilter = static_cast<MeshFilter*>(component);
    ImGui::LabelText("Mesh", meshFilter->mesh.get()->name.c_str());
    int triangles = meshFilter->mesh->indices.size()/3;
    std::string s = std::to_string(triangles);
    ImGui::LabelText("Triangles", s.c_str());
}

CUSTOM_EDITOR(MeshFilter, MeshFilterEditor);
