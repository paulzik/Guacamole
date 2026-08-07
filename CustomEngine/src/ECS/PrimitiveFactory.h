#pragma once
#include "ECS/MeshFilter.h"
#include <memory>

class PrimitiveFactory {
protected:


public:
	PrimitiveFactory();
	virtual ~PrimitiveFactory();

	static std::shared_ptr<Mesh> CreateCubePrimitive(float size = 1.0f);
	//static MeshFilter CreatePlanePrimitive(float size = 1.0f);
	// Radius 0.5 gives a unit-diameter sphere, matching the unit cube - so both
	// built-in primitives occupy the same 1x1x1 box and Transform::scale means
	// the same thing for each.
	static std::shared_ptr<Mesh> CreateSpherePrimitive(float radius = 0.5f);
};