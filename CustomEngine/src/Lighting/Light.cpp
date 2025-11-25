#include "Lighting/Light.h"
#include "ECS/Scene.h"

Light::Light(glm::vec3 _color, float _intencity) : color(_color), intensity(_intencity){
    Scene::Get().AddLight(this);
}

Light::~Light() {

}

const char* Light::GetComponentName() const {
	return "Light";
}

glm::vec3 Light::getColor() const
{
	return color;
}

float Light::getIntensity() const
{
	return intensity;
}

void Light::setIntensity(float _intencity)
{
	intensity = _intencity;
}

void Light::setColor(glm::vec3 _color)
{
	color = _color;
}
