#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "Light.h"
#include "ECS/Component.h"
#include <glm/ext/matrix_transform.hpp>

class PointLight : public Light {
private:
    float radius = 5.0f;

public:
    PointLight(glm::vec3 _color, float _intencity, float _radius = 20.0f);
    ~PointLight();

    void SetRadius(float r);
    float GetRadius();

    const char* GetComponentName() const override;

    LightType GetType() const override;

};
