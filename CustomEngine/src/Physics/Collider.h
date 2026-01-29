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

class Collider : public Component{
public:
	Collider(bool trigger) :isTrigger(trigger) {};
	virtual ~Collider() = default;
	bool isTrigger;
	void Start() override;
	void Update() override;

	virtual ColliderDescription GetColliderDescription() const = 0;

	const char* GetComponentName() const override;
private:

};