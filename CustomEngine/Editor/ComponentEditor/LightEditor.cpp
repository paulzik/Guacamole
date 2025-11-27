#include "LightEditor.h"
#include "Lighting/Light.h"
#include "EditorMacro.h"
#include <glm/gtc/type_ptr.hpp>

void LightEditor::Draw(Component* component) {
    Light* light = static_cast<Light*>(component);

    float intensity = light->GetIntensity();
    if(ImGui::SliderFloat("Intensity", &intensity, 0.0f, 1.0f)) {
        light->SetIntensity(intensity);
    }

    glm::vec3 color = light->GetColor();
    if (ImGui::ColorEdit3("Color", glm::value_ptr(color))) {
        light->SetColor(color);
    }
}

CUSTOM_EDITOR(Light, LightEditor);
