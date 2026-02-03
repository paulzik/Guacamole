#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "Light.h"
#include "ECS/Component.h"
#include <glm/ext/matrix_transform.hpp>

struct PointLight : public Light {
    float radius = 5.0f;

    PointLight(glm::vec3 _color, float _intencity, float _radius = 20.0f)
        : Light(POINT, _color, _intencity), radius(_radius)
    {
    }

    COMPONENT_NAME(PointLight);
};
