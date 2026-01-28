#pragma once
#include "Collider.h"

class SphereCollider : public Collider {
public:
    SphereCollider(bool trigger, float radius) : Collider(trigger)
    {
        m_radius = radius;
    }
    ~SphereCollider() override
    {
        // cleanup Bullet shape if owned here
    }

private:
    float m_radius;
};
