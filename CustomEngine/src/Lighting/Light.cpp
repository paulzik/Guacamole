#include "Lighting/Light.h"
#include "ECS/Scene.h"

Light::Light(LightType _type, glm::vec3 _color, float _intencity) : lightType(_type), color(_color), intensity(_intencity){
    Scene::Get().AddLight(this);
}