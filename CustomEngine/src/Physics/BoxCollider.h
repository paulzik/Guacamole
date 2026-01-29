#pragma once
#include "Collider.h"
#include <glm/vec3.hpp>

class BoxCollider : public Collider {
public:

    BoxCollider(bool trigger, glm::vec3 halfExtends) : Collider(trigger) 
    {
        m_halfExtends = halfExtends;
    }

    ~BoxCollider() override
    {
        // cleanup Bullet shape if owned here
    }

    ColliderDescription GetColliderDescription() const override;

private:
    glm::vec3 m_halfExtends;
};
