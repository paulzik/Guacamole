#pragma once
#include "Transform.h"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/quaternion.hpp"


inline glm::vec3 GetRotationEuler(const Transform& t)
{
	return glm::eulerAngles(t.rotation);
}

inline glm::vec3 GetForward(const Transform& t)
{
	return glm::normalize(t.rotation * t.up);
}