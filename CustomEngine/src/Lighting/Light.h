#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "ECS/Component.h"
#include <glm/ext/matrix_transform.hpp>

enum LightType { DIRECTIONAL = 0, POINT = 1 };

struct Light : public Component {
    LightType lightType = DIRECTIONAL;
    glm::vec3 color = glm::vec3(1.0f);
    float intensity = 1.0f;

    Light(LightType _type, glm::vec3 _color, float _intencity);

};
