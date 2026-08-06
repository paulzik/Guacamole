#pragma once
#include "Collider.h"

struct SphereCollider : public Collider {

    SphereCollider() : Collider(true) {
        colliderDescriptor.type = ColliderType::Sphere;
        colliderDescriptor.radius = 1.0f;
    }

    SphereCollider(bool trigger, float radius) : Collider(trigger)
    {
        colliderDescriptor.type = ColliderType::Sphere;
        colliderDescriptor.radius = radius;
    }

    COMPONENT_NAME(SphereCollider);

    void Reflect(IFieldVisitor& visitor) override
    {
        visitor.Visit("IsTrigger", isTrigger);
        visitor.Visit("Radius", colliderDescriptor.radius);
    }
};
