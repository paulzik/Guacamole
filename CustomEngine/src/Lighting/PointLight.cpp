#include "Lighting/Light.h"
#include "ECS/Scene.h"
#include "PointLight.h"

PointLight::PointLight(glm::vec3 _color, float _intencity, float _radius) : Light(POINT, _color, _intencity) {
    radius = _radius;
}

PointLight::~PointLight() {

}

void PointLight::SetRadius(float r)
{
    radius = r;
}

float PointLight::GetRadius()
{
    return radius;
}

const char* PointLight::GetComponentName() const
{
    return "PointLight";
}

LightType PointLight::GetType() const
{
    return POINT;
}
