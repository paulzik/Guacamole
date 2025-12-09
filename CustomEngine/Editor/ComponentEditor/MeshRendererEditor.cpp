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

    float metallic = material->metallic;
    if (ImGui::SliderFloat("Metallic", &metallic, 0.0f, 1.0f)) {
        material->metallic = metallic;
    }
}

CUSTOM_EDITOR(MeshRenderer, MeshRendererEditor);
