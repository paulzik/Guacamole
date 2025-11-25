#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "ECS/Component.h"
#include <glm/ext/matrix_transform.hpp>

class Light : public Component {
protected:
    glm::vec3 color = glm::vec3(1.0f);
    float intensity = 1.0f;

public:
    Light(glm::vec3 _color, float _intencity);
    ~Light();

    glm::vec3 getColor() const;
    float getIntensity() const;

    void setIntensity(float _intencity);
    void setColor(glm::vec3 _color);

    const char* GetComponentName() const override;
};
