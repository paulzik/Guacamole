#include "MeshRendererEditor.h"
#include "ECS/MeshRenderer.h"
#include "EditorMacro.h"
#include <glm/gtc/type_ptr.hpp>
#include <string>

void MeshRendererEditor::Draw(Component* component) {
    MeshRenderer* meshRenderer = static_cast<MeshRenderer*>(component);

    std::shared_ptr<Material> material = meshRenderer->material;

    std::string vertexShaderName = material->shader->GetVertexShader()->name;
    ImGui::LabelText("VertexShader", vertexShaderName.c_str());

    std::string fragmentShaderName = material->shader->GetFragmentShader()->name;
    ImGui::LabelText("FragmentShader", fragmentShaderName.c_str());

    if (material->albedo) {
        GLuint my_tex_id = material->albedo->ID;

        ImVec2 size(32, 32);
        ImVec2 uv0(0, 0);
        ImVec2 uv1(1, 1);
        ImVec4 bg_col(0, 0, 0, 1);
        ImVec4 tint_col(1, 1, 1, 1);

        ImGui::Text("Albedo");
        ImGui::SameLine();

        ImGui::ImageButton("##AlbedoBtn", (void*)(intptr_t)my_tex_id, size, uv0, uv1, bg_col, tint_col);
    }


    float metallic = material->metallic;
    if (ImGui::SliderFloat("Metallic", &metallic, 0.0f, 1.0f)) {
        material->metallic = metallic;
    }

    bool wireframe = meshRenderer->wireframe;
    if (ImGui::Checkbox("Wireframe", &wireframe)) {
        meshRenderer->wireframe = wireframe;
    }
}

CUSTOM_EDITOR(MeshRenderer, MeshRendererEditor);
