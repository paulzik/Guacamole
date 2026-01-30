#pragma once
#include "Collider.h"
#include <glm/vec3.hpp>

struct BoxCollider : public Collider {

    BoxCollider(bool trigger, glm::vec3 halfExtends) : Collider(trigger) 
    {
        colliderDescriptor.type = ColliderType::Box;
        colliderDescriptor.halfExtend = halfExtends;
    }

    COMPONENT_NAME(BoxCollider);
};
