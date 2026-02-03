#pragma once
#include <glm/vec3.hpp>
#include "Light.h"

struct DirectionalLight : public Light {
    glm::vec3 direction;

    DirectionalLight(const glm::vec3& _color = glm::vec3(1.0f),
        float _intensity = 1.0f,
        const glm::vec3& _direction = glm::vec3(0.0f, -1.0f, 0.0f))
        : Light(DIRECTIONAL, _color, _intensity), direction(_direction) 
    {
    }
    COMPONENT_NAME(DirectionalLight);
};
