#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "ECS/Component.h"
#include <glm/ext/matrix_transform.hpp>

enum LightType { DIRECTIONAL = 0, POINT = 1 };

class Light : public Component {
private:
    LightType lightType = DIRECTIONAL;

protected:
    glm::vec3 color = glm::vec3(1.0f);
    float intensity = 1.0f;
public:
    Light(LightType _type, glm::vec3 _color, float _intencity);
    ~Light();

    glm::vec3 GetColor() const;
    float GetIntensity() const;

    void SetIntensity(float _intencity);
    void SetColor(glm::vec3 _color);

    const char* GetComponentName() const override;

    virtual LightType GetType() const = 0;
};
