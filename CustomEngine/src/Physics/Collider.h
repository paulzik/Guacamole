#pragma once
#include "ECS/Component.h"
#include <glm/vec3.hpp>

enum class ColliderType {
    Box,
    Sphere,
    Capsule,
    Mesh
};

struct ColliderDescription {
    ColliderType type;

    // Generic data (union-like)
    glm::vec3 halfExtend;   // box half-extents
    float radius;     // sphere / capsule
    float height;     // capsule
};

struct Collider : public Component{
	Collider(bool trigger) :isTrigger(trigger) {};
	bool isTrigger;
    ColliderDescription colliderDescriptor;
};