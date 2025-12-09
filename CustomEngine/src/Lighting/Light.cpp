#include "Lighting/Light.h"
#include "ECS/Scene.h"

Light::Light(LightType _type, glm::vec3 _color, float _intencity) : lightType(_type), color(_color), intensity(_intencity){
    Scene::Get().AddLight(this);
}

Light::~Light() {

}

const char* Light::GetComponentName() const {
	return "Light";
}

glm::vec3 Light::GetColor() const
{
	return color;
}

float Light::GetIntensity() const
{
	return intensity;
}

void Light::SetIntensity(float _intencity)
{
	intensity = _intencity;
}

void Light::SetColor(glm::vec3 _color)
{
	color = _color;
}
