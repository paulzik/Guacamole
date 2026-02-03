#include "DirectionalLightEditor.h"
#include "Lighting/Light.h"
#include "Lighting/PointLight.h"
#include "Lighting/DirectionalLight.h"
#include "EditorMacro.h"
#include <glm/gtc/type_ptr.hpp>

void DirectionalLightEditor::Draw(Component* component) {
    Light* light = static_cast<Light*>(component);

    float intensity = light->intensity;
    if(ImGui::SliderFloat("Intensity", &intensity, 0.0f, 1.0f)) {
        light->intensity = intensity;
    }

    glm::vec3 color = light->color;
    if (ImGui::ColorEdit3("Color", glm::value_ptr(color))) {
        light->color = color;
    }
}

CUSTOM_EDITOR(DirectionalLight, DirectionalLightEditor);
