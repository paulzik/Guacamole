#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "Light.h"
#include <glm/ext/matrix_transform.hpp>

class DirectionalLight : public Light {
private:
    glm::vec3 direction;

public:

    DirectionalLight(glm::vec3 _color, float _intencity);
    ~DirectionalLight();

    glm::vec3 GetDirection();
    void SetDirection(glm::vec3 d);

    virtual LightType GetType() const;

    const char* GetComponentName() const override;
};
