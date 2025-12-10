#include "Lighting/Light.h"
#include "DirectionalLight.h"
#include "ECS/Scene.h"

DirectionalLight::DirectionalLight(glm::vec3 _color, float _intencity) : Light(DIRECTIONAL, _color, _intencity) {
}

DirectionalLight::~DirectionalLight() {

}

glm::vec3 DirectionalLight::GetDirection()
{
	return direction;
}

void DirectionalLight::SetDirection(glm::vec3 d)
{
	direction = d;
}

const char* DirectionalLight::GetComponentName() const {
	return "DirectionalLight";
}

LightType DirectionalLight::GetType() const
{
	return DIRECTIONAL;
}
