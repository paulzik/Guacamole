#include "PointLightEditor.h"
#include "Lighting/Light.h"
#include "Lighting/PointLight.h"
#include "Lighting/DirectionalLight.h"
#include "EditorMacro.h"
#include <glm/gtc/type_ptr.hpp>

void PointLightEditor::Draw(Component* component) {
    PointLight* pointLight = dynamic_cast<PointLight*>(component);

    float intensity = pointLight->intensity;
    if(ImGui::SliderFloat("Intensity", &intensity, 0.0f, 1.0f)) {
        pointLight->intensity = intensity;
    }

    glm::vec3 color = pointLight->color;
    if (ImGui::ColorEdit3("Color", glm::value_ptr(color))) {
        pointLight->color = color;
    }

    float radius = pointLight->radius;
    if (ImGui::SliderFloat("Radius", &radius, 0.0f, 100.0f)) {
        pointLight->radius = radius;
    }
}

CUSTOM_EDITOR(PointLight, PointLightEditor);