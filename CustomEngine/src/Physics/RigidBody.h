#pragma once
#include "ECS/Component.h"
#include <glm/fwd.hpp>


class RigidBody : public Component{
public:
    RigidBody(float m = 1.0f)
        : mass(m), friction(0.5f), restitution(0.0f),
        linearDamping(0.0f), angularDamping(0.0f),
        useGravity(true), isKinematic(false), m_InternalBody(nullptr) {
    }

    float mass;
    float friction;
    float restitution;
    float linearDamping;
    float angularDamping;
    bool useGravity;
    bool isKinematic;

    void AddForce(const glm::vec3& force);
    const char* GetComponentName() const override;

private:
    void* m_InternalBody;
    friend class PhysicsSystem;
};