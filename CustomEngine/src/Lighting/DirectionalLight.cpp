#include "Lighting/Light.h"
#include "DirectionalLight.h"
#include "ECS/Scene.h"

DirectionalLight::DirectionalLight(glm::vec3 _color, float _intencity) : Light(DIRECTIONAL, _color, _intencity) {
}

DirectionalLight::~DirectionalLight() {

}

const char* DirectionalLight::GetComponentName() const {
	return "DirectionalLight";
}

LightType DirectionalLight::GetType() const
{
	return DIRECTIONAL;
}
