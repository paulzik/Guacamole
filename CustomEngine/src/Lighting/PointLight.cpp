#include "Lighting/Light.h"
#include "ECS/Scene.h"
#include "PointLight.h"

PointLight::PointLight(glm::vec3 _color, float _intencity) : Light(POINT, _color, _intencity) {

}

PointLight::~PointLight() {

}

const char* PointLight::GetComponentName() const
{
    return "PointLight";
}

LightType PointLight::GetType() const
{
    return POINT;
}
